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
#include "timer_man.h"
#include "debug_api.h"
#include "eeprom_crc.h"
#include "time.h"

timerManager Timer;

void timerManager::init()
{

    timeinfo = localtime(&rawtime);
}


tm* timerManager::getTime()
{
    return timeinfo;
}

void timerManager::updateNTP()
{
    configTime(romdata.gmtOffset_sec, romdata.daylightOffset_sec, romdata.ntpServer);
    if (!updateLocalTime())
    {
        DEBUG(__FILENAME__, "NTP clock update failed.", t_ERROR);
    }
    else
    {
        DEBUG(__FILENAME__, "NTP clock updated.", t_INFO);
    }
}

bool timerManager::updateLocalTime()
{
    getLocalTime(timeinfo, 0);
}

/**********************************end of file**********************************/


