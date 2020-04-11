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
#define STR_BUFFER  32

struct eepromData
{
    const int     ctr_value = 150682;
    const long    gmtOffset_sec = 0;
    const int     dstOffset_sec = 0;
    const char*   ntpServer = "pool.ntp.org";
    char          sta_ssid[STR_BUFFER] = "(-_-)";
    char          sta_psk[STR_BUFFER]  = "monteiro";
    const char*   hostname = "espModule";
    const char*   ap_ssid = "espModule";
    const char*   ap_psk = "";
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

