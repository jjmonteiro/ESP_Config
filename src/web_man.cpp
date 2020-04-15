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

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "spiffs_man.h"
#include "web_socket.h"
#include "debug_api.h"
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
    if (FileSystem.exists("/index.html"))
    {
        auto thisDir = FileSystem.openRoot();
        auto thisFile = FileSystem.openNext(thisDir);

        ws.onEvent(onWsEvent);
        server.addHandler(&ws);

        server.on("/", HTTP_GET, [](AsyncWebServerRequest* request)
        {
            request->send(FileSystem, "/index.html");
        });

        server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest* request)
        {
            // DO NOT RENAME "processor". This method updates main.js with current IP address
            request->send(FileSystem, "/main.js", String(), false, processor);
        });

        while (thisFile)
        {
            String sfileName = FileSystem.getFileName(thisDir, thisFile);

            DEBUG(__FILENAME__, "Loading webserver file: " + sfileName, t_TRACE);
            server.on(sfileName.c_str(), HTTP_GET, [sfileName](AsyncWebServerRequest* request)
            {
                request->send(FileSystem, sfileName.c_str());
            });
            thisFile = FileSystem.openNext(thisDir);
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