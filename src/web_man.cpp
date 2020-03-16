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
#include "debug_api.h"
#include "SPIFFS.h"
#include "page_fail.h"
#include "web_man.h"
#include "wifi_man.h"

AsyncWebServer server(WEBSERVER_PORT);
AsyncWebSocket ws("/ws");

void notFound(AsyncWebServerRequest* request) 
{
    request->send(404, "text/plain", "Not found");
}

String processor(const String& var)
{
    if (var == "IPADDR")
    {
        if (Wifi.getMode() == WIFI_MODE_STA)
        {
            return Wifi.localIP().toString();
        }
        else
        {
            return Wifi.softAPIP().toString();
        }
    }
}

void webManager() 
{
    if (SPIFFS.exists("/index.html"))
    {
        File root = SPIFFS.open("/");
        File file = root.openNextFile();        
        ws.onEvent(onWsEvent);
        server.addHandler(&ws);

        server.on("/", HTTP_GET, [](AsyncWebServerRequest* request)
        {
            request->send(SPIFFS, "/index.html");
        });

        server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest* request)
        {
            // DO NOT RENAME "processor". This method updates main.js with current IP address
            request->send(SPIFFS, "/main.js", String(), false, processor);
        });

        if (file)
        {
            while (file)
            {
                DEBUG(__FILENAME__, "Loading webserver file: " + String(file.name()), t_TRACE);
                server.on(file.name(), HTTP_GET, [file](AsyncWebServerRequest* request)
                {
                    request->send(SPIFFS, file.name());
                });
                file = root.openNextFile();
            }
        }

        DEBUG(__FILENAME__, "SPIFFS webserver files loaded.", t_INFO);
    }
    else 
    {
        server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) 
        {
            request->send_P(200, "text/html", PAGEFAIL);
        });

        DEBUG(__FILENAME__, "PROGMEM webserver files loaded.", t_ERROR);
    }
    server.onNotFound(notFound);
    server.begin();
}

/**********************************end of file**********************************/