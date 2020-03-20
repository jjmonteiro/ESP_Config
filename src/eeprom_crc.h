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

#ifndef eeprom_crc_h
#define eeprom_crc_h

#define EEPROM_SIZE 1024

struct eepromData
{
    const long   gmtOffset_sec = 0;
    const int    dstOffset_sec = 0;
    const char*  ntpServer = "pool.ntp.org";
    char         sta_ssid[32];
    char         sta_psk[32];
    const char*  hostname = "esp32";
    const char*  ap_ssid = "esp32-123";
    const char*  ap_psk = "12345678";
};

class eepromManager
{
public:
    void init();
    void debug(dbgLevel Type);
    void readEepromData(eepromData *t);
    void writeEepromData(eepromData *t);
private:
    bool isCRCvalid(void);
    uint32_t getCRC();
    void setCRC();
};

extern eepromManager Eeprom;
extern eepromData romdata;

#endif
/**********************************end of file**********************************/

