// реализация на GyverHTTP2 + GyverWS

#pragma once

#include <DynamicWriter.h>
#include <GyverWS.h>

#include "SettingsGyverBase.h"
#include "core/DnsWrapper.h"

template <typename server_t, typename client_t, uint16_t PORT = 80>
class SettingsGyverWST : public sets::SettingsGyverBase {
   public:
#ifndef SETT_NO_DB
    SettingsGyverWST(const String& title = "", GyverDB* db = nullptr) : sets::SettingsGyverBase(title, db), server(PORT) {}
#else
    SettingsGyverWST(const String& title = "") : sets::SettingsGyverBase(title), server(PORT) {}
#endif

    // запустить. captive - запустить DNS для автооткрытия окна в режиме AP
    // domain - домен, по которому ESP будет доступна по адресу domain.local
    void begin(bool captive = true, const char* domain = nullptr) {
        setWSPort(PORT);
        _dns.begin(captive, domain);
        server.begin();
    }

    void stop() {
        server.closeAll();
        server.stop();
        _dns.stop();
    }

    void tick() {
        _dns.tick();

        RequestHeaders headers;
        if (server.available(handleHeader, &headers)) {
            if (server.isRequest()) handleRequest(server.getRequest(), headers);
            else handleMessage(server.getMessage());
            server.endEvent();
        }

        sets::SettingsBase::tick();
    }

    using sets::SettingsBase::updater;

    GyverWS<server_t, client_t> server;

   private:
    sets::DnsWrapper _dns;
    uint8_t _ws_id = 0;

    void sendWS(uint8_t* data, size_t len, bool broadcast) override {
        if (broadcast) server.sendBin(data, len);
        else server.sendBin(_ws_id, data, len);
    }

    void handleMessage(WSMessage& message) {
        if (message.type != WSMessage::Type::Bin) return;

        DynamicWriter data(UINT16_MAX);
        if (message.bounded() && (message.available() > UINT16_MAX || !data.reserve(message.available()))) return;
        if (!message.readAllTo(data)) return;

        _ws_id = message.id;
        parseWS(data.data(), data.size());
    }
};
