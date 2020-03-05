/*******************************************************************//**
 * @file    spiffs_man.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 **//*********************************************************************/

#include "Arduino.h"
#include "SPIFFS.h"
#include "debug_api.h"
#include "spiffs_man.h"

bool spiffsManager()
{
    if (!SPIFFS.begin(true)) 
    {
        Debug(__FILENAME__, "SPIFFS not mounted!", t_FATAL);
        return false;
    }
    else 
    {
        Debug(__FILENAME__, "SPIFFS mounted.", t_INFO);
        listDir("/");
        if (!SPIFFS.exists("/index.html")) 
        {
            Debug(__FILENAME__, "Couldn't find startup webpage!", t_FATAL);
            return false;
        }
        return true;
    }
}

void listDir(char* dir) 
{
    File root = SPIFFS.open(dir);
    File file = root.openNextFile();
    while (file) 
    {
        LOG("   " + String(file.name()));
        file = root.openNextFile();
    }
}

//void addFileToServer(String file) {
//    server.on(file.c_str(), HTTP_GET, [](AsyncWebServerRequest* request) {
//        request->send(SPIFFS, [&file](String a) {a = file; });
//        });
//}

/**********************************end of file**********************************/