/*******************************************************************//**
 * @file    eeprom_crc.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 *
**//*********************************************************************/

#ifndef eeprom_crc_h
#define eeprom_crc_h

#define EEPROM_SIZE 512

struct eepromData
{
    uint32_t    value1 = 0;
    uint32_t    value2 = 0;
    uint16_t    value3 = 0;
    char*       hostname = "esp32";
    char*       ssid[5][32] = { {"","","","",""} };
    char*       psk[5][32] = { {"","","","",""} };
    char*       ap_ssid = "esp32-123";
    char*       ap_psk = "12345678";
    String      str_1 = "";
    String      str_2 = "";
    String      str_3 = "";
};

class eepromManager
{
public:
    void init();
    void readEepromData(eepromData *t);
    void writeEepromData(eepromData *t);
private:
    bool isCRCvalid(void);
    uint32_t getCRC();
    void setCRC();
};

#endif
/**********************************end of file**********************************/

