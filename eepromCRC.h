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

class eepromManager {
    bool isCRCvalid(void);
    uint32_t getCRC();
    void setCRC();
public:
    void init();
    template<typename T>
    void readEepromData(const T* t);
    template<typename T>
    void writeEepromData(const T* t);
};

extern eepromManager eeprom;
#endif
/**********************************end of file**********************************/

