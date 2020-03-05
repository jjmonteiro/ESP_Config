/*******************************************************************//**
 * @file    eeprom_crc.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 *
**//*********************************************************************/

#include "Arduino.h"
#include <EEPROM.h>
#include "debug_api.h"
#include "eeprom_crc.h"

eepromManager eeprom;
eepromData romdata;

bool eepromManager::isCRCvalid(void) 
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
}

void eepromManager::readEepromData(eepromData *t)
{
    if (isCRCvalid())
    {
        Debug(__FILENAME__, "CRC test ok.", t_INFO);
        EEPROM.get(sizeof(uint32_t), *t);
    }
    else
    {
        Debug(__FILENAME__, "CRC test failed.", t_ERROR);
        writeEepromData(t);
    }
}

void eepromManager::writeEepromData(eepromData *t)
{
    EEPROM.put(sizeof(uint32_t), *t);
    EEPROM.commit() ? setCRC() : void(0);
}

/**********************************end of file**********************************/