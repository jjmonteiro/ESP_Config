/*******************************************************************//**
 * @file     timer_man.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief    Time tracking facility
 * @details  Provides date and time keeping functionality with NTP support
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

bool timerManager::updateLocalTime()
{
    return getLocalTime(timeinfo, 0);
}

tm* timerManager::getTime()
{
    return timeinfo;
}

void timerManager::updateNTP(long gmt_offset, int dst_offset, const char* ntp_server)
{
    configTime(gmt_offset, dst_offset, ntp_server);
    if (!getLocalTime(timeinfo))
    {
        DEBUG(__FILENAME__, "NTP clock update failed.", t_ERROR);
    }
    else
    {
        DEBUG(__FILENAME__, "NTP clock updated.", t_INFO);
    }
}

/**********************************end of file**********************************/


