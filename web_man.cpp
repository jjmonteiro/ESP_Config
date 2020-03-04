/*******************************************************************//**
 * @file    web_man.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 *
**//*********************************************************************/

#include "Arduino.h"
#include "ESPAsyncWebServer.h"
#include "web_socket.h"
#include "debug.h"
#include "SPIFFS.h"
#include "page_fail.h"
#include "web_man.h"

AsyncWebServer  server(WEBSERVER_PORT);
AsyncWebSocket  ws("/ws");

void notFound(AsyncWebServerRequest* request) 
{
    request->send(404, "text/plain", "Not found");
}

void webManager(bool spiffs) 
{
    if (spiffs) 
    {
        Debug(__FILENAME__, "SPIFFS server files loaded.", t_INFO);

        ws.onEvent(onWsEvent);
        server.addHandler(&ws);

        server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) 
        {
            request->send(SPIFFS, "/index.html");
        });

        server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest* request) 
        {
            request->send(SPIFFS, "/main.js", String(), false, processor);//updates main.js with current ip address
        });

        server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest* request) 
        {
            request->send(SPIFFS, "/w3.css");
        });

        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest* request) 
        {
            request->send(SPIFFS, "/style.css");
        });

        server.on("/iconify.min.js", HTTP_GET, [](AsyncWebServerRequest* request) 
        {
            request->send(SPIFFS, "/iconify.min.js");
        });
    }
    else {
        Debug(__FILENAME__, "PROGMEM server files loaded.", t_INFO);
        server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) 
        {
            request->send_P(200, "text/html", PAGEFAIL);
        });
    }

    server.onNotFound(notFound);
    server.begin();
}


String processor(const String& var) {

    if (var == "IPADDR") {
        if (WiFi.getMode() == WIFI_MODE_STA) {
            return WiFi.localIP().toString();
        }
        else {
            return WiFi.softAPIP().toString();
        }
    }
}

/**********************************end of file**********************************/