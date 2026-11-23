// реализация на GyverHTTP2

#pragma once

#include <HTServer.h>

#include "SettingsGyverBase.h"
#include "core/DnsWrapper.h"

template <typename server_t, typename client_t, uint16_t PORT = 80>
class SettingsGyverT : public sets::SettingsGyverBase {
   public:
#ifndef SETT_NO_DB
    SettingsGyverT(const String& title = "", GyverDB* db = nullptr) : sets::SettingsGyverBase(title, db), server(PORT) {}
#else
    SettingsGyverT(const String& title = "") : sets::SettingsGyverBase(title), server(PORT) {}
#endif

    // запустить. captive - запустить DNS для автооткрытия окна в режиме AP
    // domain - домен, по которому ESP будет доступна по адресу domain.local
    void begin(bool captive = true, const char* domain = nullptr) {
        _dns.begin(captive, domain);
        server.begin();
    }

    void stop() {
        server.stop();
        _dns.stop();
    }

    void tick() {
        _dns.tick();

        RequestHeaders headers;
        if (server.available(handleHeader, &headers)) {
            handleRequest(server.getRequest(), headers);
            server.endRequest();
        }

        sets::SettingsBase::tick();
    }

    using sets::SettingsBase::updater;

    HTServer<server_t, client_t> server;

   private:
    sets::DnsWrapper _dns;
};
