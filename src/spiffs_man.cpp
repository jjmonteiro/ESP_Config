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

spiffsManager FileSystem;

bool spiffsManager::init()
{
    bool result = false;
    if (SPIFFS.begin())
    {
        DEBUG(__FILENAME__, "SPIFFS mounted.", t_INFO);
        printRoot(t_INFO);
        result = true;
    }
    else 
    {
        DEBUG(__FILENAME__, "SPIFFS not mounted!", t_ERROR);
    }
    return result;
}

void spiffsManager::printRoot(dbgLevel Type)
{
    if (DEBUG_LEVEL <= Type)
    {
        File root = SPIFFS.open("/");
        File file = root.openNextFile();
        if (file)
        {
            while (file) 
            {
                PRINT_LINE("   " + String(file.name()));
                file = root.openNextFile();
            }
        }
        else
        {
            DEBUG(__FILENAME__, "No files found.", t_ERROR);
        }
    }
}

/**********************************end of file**********************************/