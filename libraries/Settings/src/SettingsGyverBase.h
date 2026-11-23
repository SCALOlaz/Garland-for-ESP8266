#pragma once

#include <Arduino.h>
#include <HTServer.h>
#include <LittleFS.h>
#include <stdlib.h>

#include "core/SettingsBase.h"
#include "core/ota.h"
#include "web/settings.h"

namespace sets {

// Общая реализация протокола для транспортов GyverHTTP2/GyverWS
class SettingsGyverBase : public SettingsBase {
   public:
#ifndef SETT_NO_DB
    SettingsGyverBase(const String& title = "", GyverDB* db = nullptr) : SettingsBase(title, db) {
        setUploadBody();
    }
#else
    SettingsGyverBase(const String& title = "") : SettingsBase(title) {
        setUploadBody();
    }
#endif

   protected:
    struct RequestHeaders {
        size_t auth = 0;
        size_t action = 0;
        size_t id = 0;
    };

    static void handleHeader(void* context, char* name, char* value) {
        RequestHeaders& headers = *(RequestHeaders*)context;
        if (!strcasecmp_P(name, PSTR("Auth"))) {
            headers.auth = Text(value).toInt32HEX();
        } else if (!strcasecmp_P(name, PSTR("Action"))) {
            headers.action = Text(value).hash();
        } else if (!strcasecmp_P(name, PSTR("Id"))) {
            headers.id = Text(value).toInt32HEX();
        }
    }

    void handleRequest(HTServerRequest& request, const RequestHeaders& headers) {
        if (request.method == HT_OPTIONS) {
            sendCode(request, 204);
            return;
        }

        switch (request.pathHash()) {
            case HTH("/discover"): {
                if (!isMethod(request, HT_GET)) return;

                ResponseContext response(request);
                _response = &response;
                parse(0, SH("discover"), 0, Text());
                _response = nullptr;
            } break;

            case HTH("/settings"): {
                if (!isMethod(request, HT_POST) || !checkFixedBody(request)) return;

                uint32_t len = request.available();
                if (len > UINT16_MAX) {
                    sendCode(request, 413);
                    return;
                }

                uint8_t* value = (uint8_t*)malloc(len);

                if (request.readAll(value)) {
                    ResponseContext response(request);
                    _response = &response;
                    parse(headers.auth, headers.action, headers.id, Text(value, len));
                    _response = nullptr;
                } else {
                    sendCode(request, 500);
                }

                free(value);
            } break;

            case HTH("/fetch"): {
                if (!checkAuthorized(request, headers, HT_GET)) return;

                String path = request.decodeParam("path");
                File file = fs.openRead(path.c_str());
                if (!file) {
                    sendCode(request, 404);
                    return;
                }

                auto resp = request.responseSingle();
                resp.setType(HTMime::bin);
                setCORS(resp);
                resp.send(file, file.size());
                if (fetch_cb) fetch_cb(path);
            } break;

            case HTH("/upload"): {
                if (!checkAuthorized(request, headers, HT_POST) || !checkFixedBody(request)) return;

                String path = request.decodeParam("path");
                File file = fs.openWrite(path.c_str());
                bool ok = file && request.readAllTo(file);
                if (file) file.close();

                sendCode(request, ok ? 200 : 500);
                if (ok && upload_cb) upload_cb(path);
            } break;

            case HTH("/ota"): {
                if (!checkAuthorized(request, headers, HT_POST) || !checkFixedBody(request)) return;

                bool started = beginOta();
                bool ok = started && request.readAllTo(Update);
                if (started) {
                    if (ok) ok = Update.end(true) && !Update.hasError();
                    else Update.end();
                }
                sendCode(request, ok ? 200 : 500);
                if (ok) restart();
            } break;

            case HTH("/script.js"):
                sendPGM(request, HTMime::js, settings_script_gz, sizeof(settings_script_gz), true, true);
                break;

            case HTH("/style.css"):
                sendPGM(request, HTMime::css, settings_style_gz, sizeof(settings_style_gz), true, true);
                break;

            case HTH("/favicon.svg"):
                sendPGM(request, HTMime::svg, settings_favicon_gz, sizeof(settings_favicon_gz), true, true);
                break;

            case HTH("/custom.js"):
                sendCustom(request);
                break;

            default:
                sendPGM(request, HTMime::html, settings_index_gz, sizeof(settings_index_gz), true, false);
                break;
        }
    }

   private:
    struct ResponseContext {
        ResponseContext(HTServerRequest& request) : request(request) {}

        void answer(uint8_t* data, size_t len, bool last) {
            if (last && !chunked.isWriting()) {
                auto response = request.responseSingle();
                setCORS(response);
                response.setType(HTMime::bin);
                response.send(data, len);
                return;
            }

            if (!chunked) {
                chunked = request.responseChunked();
                if (!chunked) {
                    if (!request.handled()) request.sendResponse(505);
                    return;
                }
                setCORS(chunked);
                chunked.setType(HTMime::bin);
                if (!chunked.begin()) return;
            }

            chunked.write(data, len);
            if (last) chunked.end();
        }

       private:
        HTServerRequest& request;
        HTChunkedWriter chunked;
    };

    ResponseContext* _response = nullptr;

    void answer(uint8_t* data, size_t len, bool last) override {
        if (_response) _response->answer(data, len, last);
    }

    bool isMethod(HTServerRequest& request, HTMethod method) {
        if (request.method == method) return true;
        sendCode(request, 405);
        return false;
    }

    bool authorize(HTServerRequest& request, const RequestHeaders& headers) {
        if (authenticate(headers.auth)) return true;
        sendCode(request, 401);
        return false;
    }

    bool checkAuthorized(HTServerRequest& request, const RequestHeaders& headers, HTMethod method) {
        return isMethod(request, method) && authorize(request, headers);
    }

    bool checkFixedBody(HTServerRequest& request) {
        if (!request.chunked()) return true;
        sendCode(request, 411);
        return false;
    }

    void sendCode(HTServerRequest& request, uint16_t code) {
#ifdef SETS_NO_CORS
        request.sendResponse(code);
#else
        auto response = request.responseSingle(code);
        setCORS(response, request.method == HT_OPTIONS);
        response.send();
#endif
    }

    void sendPGM(HTServerRequest& request, HTMime mime, const uint8_t* data, size_t len, bool gzip, bool cache) {
        auto response = request.responseSingle();
        setCORS(response);
        response.setType(mime);
        if (gzip) response.setGzip();
        response.setCache(cache ? (7ul * 24 * 60 * 60) : 0);
        response.send(data, len, true);
    }

    void sendCustom(HTServerRequest& request) {
        if (!custom.p) {
            sendCode(request, 500);
            return;
        }

        File file;
        auto response = request.responseSingle();
        setCORS(response);
        response.setType(HTMime::js);
        if (custom.gz) response.setGzip();

        if (!custom.isFile) {
            response.send(custom.p, custom.len, true);
        } else {
            file = fs.openRead(custom.p);
            if (!file) {
                sendCode(request, 500);
                return;
            }
            response.send(file, file.size());
        }
    }

    static void setCORS(HTMessage& hdr, bool preflight = false) {
#ifndef SETS_NO_CORS
        hdr.setCORS();
        if (preflight) hdr.addHeader(F("Access-Control-Allow-Headers"), F("Auth, Action, Id, Content-Type"));
#else
        (void)hdr;
        (void)preflight;
#endif
    }
};

}  // namespace sets
