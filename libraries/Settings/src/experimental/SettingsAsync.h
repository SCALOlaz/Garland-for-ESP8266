// реализация на ESP32Async/ESPAsyncWebServer

#pragma once
#include <Arduino.h>
#include <LittleFS.h>
#include <stdlib.h>

#include <new>

#ifdef ESP8266
#include <ESPAsyncTCP.h>
#else
#include <AsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#include "core/DnsWrapper.h"
#include "core/SettingsBase.h"
#include "core/ota.h"
#include "web/settings.h"

class SettingsAsync : public sets::SettingsBase {
   public:
#ifndef SETT_NO_DB
    SettingsAsync(const String& title = "", GyverDB* db = nullptr) : sets::SettingsBase(title, db), server(80) {}
#else
    SettingsAsync(const String& title = "") : sets::SettingsBase(title), server(80) {}
#endif

    // запустить. captive - запустить mdns для автооткрытия окна в режиме AP при подключении к точке
    // domain - домен, по которому есп будет доступна в локальной сети по адресу домен.local
    void begin(bool captive = true, const char* domain = nullptr) {
        _dns.begin(captive, domain);

        server.on("/discover", HTTP_GET, [this](AsyncWebServerRequest* request) {
            _response = request->beginResponseStream("text/plain");
            cors_h(_response);
            parse(0, SH("discover"), 0, Text());
            request->send(_response);
            _response = nullptr;
        });

        server.on("/settings", HTTP_GET, [this](AsyncWebServerRequest* request) {
            String auth, action, id, value;
            if (request->hasParam("auth")) auth = request->getParam("auth")->value();
            if (request->hasParam("action")) action = request->getParam("action")->value();
            if (request->hasParam("id")) id = request->getParam("id")->value();
            if (request->hasParam("value")) value = request->getParam("value")->value();

            _response = request->beginResponseStream("text/plain");
            cors_h(_response);
            parse(Text(auth).toInt32HEX(),
                  Text(action).hash(),
                  Text(id).toInt32HEX(),
                  value);
            request->send(_response);
            _response = nullptr;
        });

        server.on("/fetch", HTTP_GET, [this](AsyncWebServerRequest* request) {
            String auth, path;
            if (request->hasParam("auth")) auth = request->getParam("auth")->value();
            if (request->hasParam("path")) path = request->getParam("path")->value();

            if (!authenticate(auth)) {
                sendCode(401, request);
            } else if (fs.fs(path.c_str())) {
                AsyncWebServerResponse* response = request->beginResponse(*(fs.fs(path.c_str())), path, "application/octet-stream");
                cors_h(response);
                request->send(response);
                if (fetch_cb) fetch_cb(path);
            } else {
                sendCode(404, request);
            }
        });

        server.on("/upload", HTTP_POST, [this](AsyncWebServerRequest* request) {
            TransferState *state = static_cast<TransferState *>(request->_tempObject);
            sendCode(!state ? 500 : (!state->authorized ? 401 : (state->ok ? 200 : 500)), request);
            free(state);
            request->_tempObject = nullptr; }, [this](AsyncWebServerRequest* request, String filename, size_t index, uint8_t* data, size_t len, bool final) {
            String auth, path;
            if (request->hasParam("auth")) auth = request->getParam("auth")->value();
            if (request->hasParam("path")) path = request->getParam("path")->value();

            if (!index) {
                void *storage = malloc(sizeof(TransferState));
                TransferState *state = storage ? new (storage) TransferState : nullptr;
                request->_tempObject = state;
                if (!state) return;
                request->onDisconnect([request]() {
                    TransferState *state = static_cast<TransferState *>(request->_tempObject);
                    if (!state) return;
                    if (request->_tempFile) request->_tempFile.close();
                    free(state);
                    request->_tempObject = nullptr;
                });
                state->authorized = authenticate(auth);
                if (state->authorized) {
                    request->_tempFile = fs.openWrite(path.c_str());
                    state->ok = (bool)request->_tempFile;
                }
            }

            TransferState *state = static_cast<TransferState *>(request->_tempObject);
            if (!state || !state->authorized) return;
            if (len && state->ok) state->ok = request->_tempFile.write(data, len) == len;
            if (final) {
                if (request->_tempFile) request->_tempFile.close();
                if (state->ok && upload_cb) upload_cb(path);
            } });

        server.on("/ota", HTTP_POST, [this](AsyncWebServerRequest* request) {
            TransferState *state = static_cast<TransferState *>(request->_tempObject);
            sendCode(!state ? 500 : (!state->authorized ? 401 : (state->ok ? 200 : 500)), request);
            bool restartRequired = state && state->authorized && state->ok;
            free(state);
            request->_tempObject = nullptr;
            if (restartRequired) restart(); }, [this](AsyncWebServerRequest* request, String filename, size_t index, uint8_t* data, size_t len, bool final) {
            String auth;
            if (request->hasParam("auth")) auth = request->getParam("auth")->value();

            if (!index) {
                void *storage = malloc(sizeof(TransferState));
                TransferState *state = storage ? new (storage) TransferState : nullptr;
                request->_tempObject = state;
                if (!state) return;
                request->onDisconnect([request]() {
                    TransferState *state = static_cast<TransferState *>(request->_tempObject);
                    if (!state) return;
                    if (state->otaActive) Update.end();
                    free(state);
                    request->_tempObject = nullptr;
                });
                state->authorized = authenticate(auth);
                state->ok = state->authorized && sets::beginOta(true);
                state->otaActive = state->ok;
            }

            TransferState *state = static_cast<TransferState *>(request->_tempObject);
            if (!state || !state->authorized) return;
            if (len && state->ok) state->ok = Update.write(data, len) == len;
            if (final) {
                if (state->ok) state->ok = Update.end(true) && !Update.hasError();
                else if (state->otaActive) Update.end();
                state->otaActive = false;
            } });

        server.onNotFound([this](AsyncWebServerRequest* request) {
            if (request->method() == HTTP_OPTIONS) {
                sendCode(204, request);
                return;
            }
            AsyncWebServerResponse* response = request->beginResponse(200, "text/html", settings_index_gz, sizeof(settings_index_gz));
            gzip_h(response);
            no_cache_h(response);
            request->send(response);
        });
        server.on("/script.js", HTTP_GET, [this](AsyncWebServerRequest* request) {
            AsyncWebServerResponse* response = request->beginResponse(200, "text/javascript", settings_script_gz, sizeof(settings_script_gz));
            gzip_h(response);
            cache_h(response);
            request->send(response);
        });
        server.on("/style.css", HTTP_GET, [this](AsyncWebServerRequest* request) {
            AsyncWebServerResponse* response = request->beginResponse(200, "text/css", settings_style_gz, sizeof(settings_style_gz));
            gzip_h(response);
            cache_h(response);
            request->send(response);
        });
        server.on("/favicon.svg", HTTP_GET, [this](AsyncWebServerRequest* request) {
            AsyncWebServerResponse* response = request->beginResponse(200, "image/svg+xml", settings_favicon_gz, sizeof(settings_favicon_gz));
            gzip_h(response);
            cache_h(response);
            request->send(response);
        });
        server.on("/custom.js", HTTP_GET, [this](AsyncWebServerRequest* request) {
            if (!custom.p || (custom.isFile && !fs.fs(custom.p))) {
                sendCode(500, request);
            } else {
                AsyncWebServerResponse* response;
                if (!custom.isFile) response = request->beginResponse(200, "text/javascript", (const uint8_t*)custom.p, custom.len);
                else response = request->beginResponse(*(fs.fs(custom.p)), custom.p, "text/javascript");
                if (!response) return;

                if (custom.gz) gzip_h(response);
                cors_h(response);
                request->send(response);
            }
        });
        beginExtra();
        server.begin();
    }

    void stop() {
        stopExtra();
        server.end();
        _dns.stop();
    }

    void tick() {
        _dns.tick();
        tickExtra();
        sets::SettingsBase::tick();
    }

   protected:
    AsyncWebServer server;

    virtual void beginExtra() {}
    virtual void stopExtra() {}
    virtual void tickExtra() {}

   private:
    struct TransferState {
        bool authorized = false;
        bool ok = false;
        bool otaActive = false;
    };

    AsyncResponseStream* _response = nullptr;
    sets::DnsWrapper _dns;

    String getMac() override {
        return WiFi.macAddress();
    }
    int getRSSI() override {
        return constrain(2 * (WiFi.RSSI() + 100), 0, 100);
    }
    IPAddress getIP() override {
        return WiFi.localIP();
    }

    void answer(uint8_t* data, size_t len, bool last) override {
        (void)last;
        if (_response) _response->write(data, len);
    }

    void sendCode(int code, AsyncWebServerRequest* request) {
        AsyncWebServerResponse* response = request->beginResponse(code);
        cors_h(response);
        request->send(response);
    }

    void gzip_h(AsyncWebServerResponse* response) {
        response->addHeader(F("Content-Encoding"), F("gzip"));
    }
    void cache_h(AsyncWebServerResponse* response) {
        response->addHeader(F("Cache-Control"), F("max-age=604800"));
    }
    void no_cache_h(AsyncWebServerResponse* response) {
        response->addHeader(F("Cache-Control"), F("no-cache, no-store, must-revalidate"));
        response->addHeader(F("Pragma"), F("no-cache"));
        response->addHeader(F("Expires"), F("0"));
    }
    void cors_h(AsyncWebServerResponse* response) {
#ifndef SETS_NO_CORS
        response->addHeader(F("Access-Control-Allow-Origin"), F("*"));
        response->addHeader(F("Access-Control-Allow-Private-Network"), F("true"));
        response->addHeader(F("Access-Control-Allow-Methods"), F("*"));
#endif
    }
};
