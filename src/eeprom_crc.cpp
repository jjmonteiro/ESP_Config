/*******************************************************************//**
 * @file     eeprom_crc.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief    EEPROM handling facility
 * @details  Provides a CRC safe EEPROM interface for reading and writing
 *           application and user data.
 *
**//*********************************************************************/

#include "Arduino.h"
#if defined ESP32
#include <rom/rtc.h>
#endif
#include <EEPROM.h>
#include "debug_api.h"
#include "eeprom_crc.h"

eepromManager Eeprom;
eepromData romdata;

void eepromManager::debug(dbgLevel Type)
{
    if (DEBUG_LEVEL <= Type)
    {
        PRINT_LINE("   gmtOffset_sec: " + String(romdata.gmtOffset_sec));
        PRINT_LINE("   dstOffset_sec: " + String(romdata.dstOffset_sec));
        PRINT_LINE("   ntpServer: " + String(romdata.ntpServer));
        PRINT_LINE("   sta_ssid: " + String(romdata.sta_ssid));
        PRINT_LINE("   sta_psk: " + String(romdata.sta_psk));
        PRINT_LINE("   hostname: " + String(romdata.hostname));
        PRINT_LINE("   ap_ssid: " + String(romdata.ap_ssid));
        PRINT_LINE("   ap_psk: " + String(romdata.ap_psk));
        PRINT_LINE("   ctr_value: " + String(romdata.ctr_value));
    }
}

bool eepromManager::isCRCvalid() 
{
    uint32_t crc;
    EEPROM.get(0, crc);
    return (crc == getCRC());
}

uint32_t eepromManager::getCRC()
{
    uint32_t crc = ~0L;
    const uint32_t crc_table[16] = 
    {
        0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
        0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
        0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
        0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
    };
    for (int index = sizeof(crc); index < EEPROM_SIZE; ++index) 
    {
        crc = crc_table[(crc ^ EEPROM.read(index)) & 0x0f] ^ (crc >> 4);
        crc = crc_table[(crc ^ (EEPROM.read(index) >> 4)) & 0x0f] ^ (crc >> 4);
        crc = ~crc;
    }
    return (crc);
}

void eepromManager::setCRC()
{
    uint32_t crc = getCRC();
    EEPROM.put(0, crc);
    EEPROM.commit();
}

void eepromManager::init() 
{
    EEPROM.begin(EEPROM_SIZE);
    readEepromData(&romdata);
    if (romdata.ctr_value != 150682)
    {
        DEBUG(__FILENAME__, "CTR value check failed. Defaults loaded.", t_ERROR);
        eepromData loadDefaults;
        writeEepromData(&loadDefaults);
    }
}

void eepromManager::readEepromData(eepromData *t)
{
    if (isCRCvalid())
    {
        DEBUG(__FILENAME__, "CRC test ok.", t_INFO);
        EEPROM.get(sizeof(uint32_t), t);
        eepromManager::debug(t_TRACE);
    }
    else
    {
        DEBUG(__FILENAME__, "CRC test failed. Defaults loaded.", t_ERROR);
        eepromManager::writeEepromData(t);
    }
}

void eepromManager::writeEepromData(eepromData *t)
{
    EEPROM.put(sizeof(uint32_t), t);
    if (EEPROM.commit())
    {
        eepromManager::setCRC();
        DEBUG(__FILENAME__, "EEPROM write success.", t_TRACE);
    }
    else
    {
        DEBUG(__FILENAME__, "EEPROM write failed.", t_ERROR);
    }
}

/**********************************end of file**********************************/