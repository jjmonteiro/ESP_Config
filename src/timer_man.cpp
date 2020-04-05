/*******************************************************************//**
 * @file     timer_man.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief    Time tracking facility
 * @details  Provides date and time keeping functionality with NTP support
 *
 **//*********************************************************************/

#include <Arduino.h>
#include "time.h"
#include "timer_man.h"
#include "debug_api.h"
#include "eeprom_crc.h"

timerManager Timer;

void timerManager::init()
{
    timeinfo = localtime(&rawtime);
    updateLocalTime();
    DEBUG(__FILENAME__, "Timer manager initiated.", t_INFO);
}

#ifdef ESP32
bool timerManager::updateLocalTime()
{
    return getLocalTime(timeinfo, 0);
}

bool timerManager::updateTimeServer()
{
    return getLocalTime(timeinfo);
}
#else
bool timerManager::updateLocalTime()
{
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return rawtime;
}

bool timerManager::updateTimeServer()
{
    timeinfo = localtime(&rawtime);
    return rawtime;
}
#endif

tm* timerManager::getTime()
{
    return timeinfo;
}

void timerManager::updateNTP(long gmt_offset, int dst_offset, const char* ntp_server)
{
    configTime(gmt_offset, dst_offset, ntp_server);

    if (updateTimeServer())
    {
        DEBUG(__FILENAME__, "NTP clock updated.", t_INFO);
    }
    else
    {
        DEBUG(__FILENAME__, "NTP clock update failed.", t_ERROR);
    }
}

/**********************************end of file**********************************/


