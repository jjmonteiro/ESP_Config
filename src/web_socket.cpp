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

#include <Arduino.h>
#include <AsyncWebSocket.h>
#include <ArduinoJson.h>
#include "debug_api.h"
#include "web_socket.h"
#include "wifi_man.h"
#include "spiffs_man.h"

//StaticJsonDocument<200> jsonReceiveBuffer;//using stack
//StaticJsonDocument<200> jsonSendBuffer;//using stack
DynamicJsonDocument jsonIncomingBuffer(JSON_INCOMING_BUFFER);//using heap
DynamicJsonDocument jsonOutgoingBuffer(JSON_OUTGOING_BUFFER);//using heap

void onWsEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) 
{
    String cliendID = "CLIENT_" + String(client->id());

    if (type == WS_EVT_CONNECT) 
    {
        DEBUG(__FILENAME__, "WS_EVT_CONNECT_" + cliendID, t_INFO);
        //Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
        //client->printf("Hello Client %u :)", client->id());
        //client->ping();
    }
    else if (type == WS_EVT_DISCONNECT) 
    {
        DEBUG(__FILENAME__, "WS_EVT_DISCONNECT_" + cliendID, t_INFO);
    }
    else if (type == WS_EVT_ERROR) 
    {
        DEBUG(__FILENAME__, "WS_EVT_ERROR_" + cliendID + " CODE:" + String(*((uint16_t*)arg)) + " DATA:" + String((char*)data), t_ERROR);
    }
    else if (type == WS_EVT_DATA) 
    {
        AwsFrameInfo* info = (AwsFrameInfo*)arg;
        String msg = "";
        String reply = "";
        jsonIncomingBuffer.clear();
        jsonOutgoingBuffer.clear();

        if (info->final && info->index == 0 && info->len == len) 
        {
            //the whole message is in a single frame and we got all of it's data
            //Serial.printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);

            if (info->opcode == WS_TEXT) 
            {
                for (size_t i = 0; i < info->len; i++) 
                {
                    msg += (char)data[i];
                }
            }

            DEBUG(__FILENAME__, "WS_EVT_DATA_" + cliendID + " REQUEST:" + String(msg.c_str()), t_TRACE);

            DeserializationError error = deserializeJson(jsonIncomingBuffer, msg.c_str());
            if (error) 
            {
                DEBUG(__FILENAME__, "WS_EVT_DATA_JSON_FAIL_" + cliendID + " CODE:" + String(error.c_str()), t_ERROR);
            }

            uint8_t web_request_type = jsonIncomingBuffer["type"];
            jsonOutgoingBuffer["type"] = web_request_type;

            JsonArray value = jsonOutgoingBuffer.createNestedArray("value");

            switch (web_request_type)
            {
            case 0:
                break;
            case 1:
                break;
            case 2:
            {
                JsonObject key = value.createNestedObject();
                const uint8_t cn_UPPER_MAP_LIMIT = 100;

                key["battery"] = random(100);//map(value, fromLow, fromHigh, toLow, toHigh)
                key["memory"]  = map(ESP_USED_HEAP, 0, ESP_HEAP_SIZE, 0, cn_UPPER_MAP_LIMIT);
                key["storage"] = map(FileSystem.getUsedBytes(), 0, FileSystem.getTotalBytes(), 0, cn_UPPER_MAP_LIMIT);
                break;
            }
            case 3:
            {
                int numNetworks = WiFi.scanComplete();

                if ((numNetworks == WIFI_SCAN_FAILED) || (numNetworks == WIFI_SCAN_RUNNING))
                {
                    WiFi.scanNetworks(true);
                }
                else if (numNetworks)
                {
                    DEBUG(__FILENAME__, "Scan complete. Wifi networks found: " + String(numNetworks), t_TRACE);
                    for (uint8_t i = 0; i < numNetworks; ++i)
                    {
                        JsonObject key = value.createNestedObject();
                        key["SSID"] = Wifi.SSID(i);
                        key["RSSI"] = Wifi.RSSI(i);
                        key["CH"]   = Wifi.channel(i);
                        key["AUTH"] = Wifi.getEncriptionType(i);
                    }
                    WiFi.scanDelete();
                    WiFi.scanNetworks(true);
                }
            }
            default:
                break;
            }

            serializeJson(jsonOutgoingBuffer, reply);
            DEBUG(__FILENAME__, "WS_EVT_DATA_" + cliendID + " REPLY:" + reply, t_TRACE);
            client->text(reply);
        }
        else 
        {
            DEBUG(__FILENAME__, "WS_EVT_DATA_MSG_TOO_BIG_" + cliendID, t_ERROR);
        }
    }
}

/**********************************end of file**********************************/