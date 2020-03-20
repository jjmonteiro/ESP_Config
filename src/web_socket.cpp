/*******************************************************************//**
 * @file    web_socket.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 *
**//*********************************************************************/

#include "Arduino.h"
#include "AsyncWebSocket.h"
#include <ArduinoJson.h>
#include "SPIFFS.h"
#include "debug_api.h"
#include "web_socket.h"
#include "wifi_man.h"

//StaticJsonDocument<200> jsonReceiveBuffer;//using stack
//StaticJsonDocument<200> jsonSendBuffer;//using stack
DynamicJsonDocument jsonReceiveBuffer(2048);//using heap
DynamicJsonDocument jsonSendBuffer(2048);//using heap

void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {

    String cliendID = "CLIENT_" + String(client->id()) + ": ";

    if (type == WS_EVT_CONNECT) {
        DEBUG(__FILENAME__, "WS_EVT_CONNECT " + String(client->id()), t_INFO);
        //Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
        //client->printf("Hello Client %u :)", client->id());
        //client->ping();
    }
    else if (type == WS_EVT_DISCONNECT) {
        DEBUG(__FILENAME__, "WS_EVT_DISCONNECT " + String(client->id()), t_INFO);
    }
    else if (type == WS_EVT_ERROR) {
        DEBUG(__FILENAME__, "WS_EVT_ERROR " + String(client->id()) + " Code: " + String(*((uint16_t*)arg)) + " Error Data: " + String((char*)data), t_ERROR);
    }
    else if (type == WS_EVT_DATA) {
        AwsFrameInfo* info = (AwsFrameInfo*)arg;
        String msg = "";
        String reply = "";
        jsonReceiveBuffer.clear();
        jsonSendBuffer.clear();

        if (info->final && info->index == 0 && info->len == len) {
            //the whole message is in a single frame and we got all of it's data
            //Serial.printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);

            if (info->opcode == WS_TEXT) {
                for (size_t i = 0; i < info->len; i++) {
                    msg += (char)data[i];
                }
            }

            //Debug(__FILENAME__, "WS_EVT_DATA " + String(client->id()) + " Request: " + String(msg.c_str()), t_INFO);
            ////Serial.printf("%s\n", msg.c_str());

            DeserializationError error = deserializeJson(jsonReceiveBuffer, msg.c_str());

            // Test if parsing succeeds.
            if (error) {
                Serial.print(F("deserializeJson() failed: "));
                Serial.println(error.c_str());
                return;
            }

            int type = jsonReceiveBuffer["type"];
            jsonSendBuffer["type"] = type;

            JsonArray value = jsonSendBuffer.createNestedArray("value");


            switch (type) {
            case 0:
                break;
            case 1:
                break;
            case 2:
            {
                JsonObject key = value.createNestedObject();
                key["battery"] = random(100);//map(value, fromLow, fromHigh, toLow, toHigh)
                key["memory"] = map((ESP.getHeapSize() - ESP.getFreeHeap()), 0, ESP.getHeapSize(), 0, 100);
                key["storage"] = map(SPIFFS.usedBytes(), 0, SPIFFS.totalBytes(), 0, 100);
                break;
            }
            case 3:
            {
                int n = Wifi.scanNetworks();
                for (int i = 0; i < n; ++i) {
                    JsonObject key = value.createNestedObject();
                    key["SSID"] = Wifi.SSID(i);
                    key["RSSI"] = Wifi.RSSI(i);
                    key["CH"] = Wifi.channel(i);
                    key["AUTH"] = String(translateEncryptionType(Wifi.encryptionType(i)));
                    //key["MAC"] = String(WiFi.BSSIDstr(i));
                    delay(10);
                }
                break;
            }
            default:
                break;
            }

            serializeJson(jsonSendBuffer, reply);
            //Debug(__FILENAME__, "WS_EVT_DATA: " + reply, t_INFO);
            client->text(reply);

        }
        else {
            DEBUG(__FILENAME__, "WS_EVT_DATA - Message too big was ignored.", t_ERROR);
        }
    }
}

String translateEncryptionType(wifi_auth_mode_t encryptionType) {

    switch (encryptionType) {
    case (WIFI_AUTH_OPEN):
        return "Open";
    case (WIFI_AUTH_WEP):
        return "WEP";
    case (WIFI_AUTH_WPA_PSK):
        return "WPA1";
    case (WIFI_AUTH_WPA2_PSK):
        return "WPA2";
    case (WIFI_AUTH_WPA_WPA2_PSK):
        return "WPA1/2";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
        return "WPA2/E";
    default:
        return "OTHER";
    }
}

/**********************************end of file**********************************/