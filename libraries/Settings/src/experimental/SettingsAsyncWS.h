#pragma once

#include "SettingsAsync.h"

class SettingsAsyncWS : public SettingsAsync {
   public:
    using SettingsAsync::SettingsAsync;

    void onUpdate(UpdateCallback cb) = delete;
    using SettingsAsync::updater;

   private:
    AsyncWebSocket ws{"/"};
    uint32_t _id = 0;

    void beginExtra() override {
        setWSPort(80);
        ws.onEvent([this](AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
            if (type != WS_EVT_DATA) return;

            AwsFrameInfo* info = static_cast<AwsFrameInfo*>(arg);
            if (!info || info->opcode != WS_BINARY || !info->final || info->index || info->len != len) return;

            _id = client->id();
            parseWS(data, len);
        });
        server.addHandler(&ws);
    }

    void stopExtra() override {
        ws.closeAll();
    }

    void tickExtra() override {
        ws.cleanupClients();
    }

    void sendWS(uint8_t* data, size_t len, bool broadcast) override {
        broadcast ? ws.binaryAll(data, len) : ws.binary(_id, data, len);
    }
};
