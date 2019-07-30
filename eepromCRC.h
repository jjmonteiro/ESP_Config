/*
  Eeprom wrapper library for Espressif MCUs
  Copyright (c) 2019 Joaquim Monteiro. All rights reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _EEPROMCRC_h
#define _EEPROMCRC_h

#include "Arduino.h"
#include <EEPROM.h>

#define EEPROM_SIZE 512


class eepromManager {

    bool isCRCvalid(void) {

        uint32_t crc;
        EEPROM.get(0, crc);
        return (crc == getCRC());

    }

    uint32_t getCRC() {
        uint32_t crc = ~0L;
        const uint32_t crc_table[16] = {
            0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
            0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
            0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
            0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
        };
        for (int index = sizeof(crc); index < EEPROM_SIZE; ++index) {
            crc = crc_table[(crc ^ EEPROM.read(index)) & 0x0f] ^ (crc >> 4);
            crc = crc_table[(crc ^ (EEPROM.read(index) >> 4)) & 0x0f] ^ (crc >> 4);
            crc = ~crc;
        }
        return (crc);
    }

    void setCRC() {
        uint32_t crc = getCRC();
        EEPROM.put(0, crc);
        EEPROM.commit();
    }

public:

    void init() {
        EEPROM.begin(EEPROM_SIZE);
    }

    template<typename T>
    void readEepromData(const T* t) {
        if (isCRCvalid()) {
            EEPROM.get(sizeof(uint32_t), *t);
        }
        else {
            writeEepromData(t);
        }
    }

    template<typename T>
    void writeEepromData(const T* t) {

        EEPROM.put(sizeof(uint32_t), *t);

        if (EEPROM.commit()) {
            setCRC();
        }
    }
};


#endif

