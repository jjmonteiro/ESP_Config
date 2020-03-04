/*******************************************************************//**
 * @file    debug.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief   Debugger reporting facility
 * @details Generic implementation and definitions for the debug facility, 
 * provided for internal use and code troubleshooting
 * 
**//*********************************************************************/

#ifndef debug_h
#define debug_h

#include <rom/rtc.h>
#include "eeprom_crc.h"
#include "version.h"
#include <string.h>

typedef enum dbgLevel {
    t_DEBUG,
    t_INFO,
    t_WARN,
    t_ERROR,
    t_FATAL
};

#define SERIAL_BAUDRATE	115200
#define LOG(x) Serial.println(x)
#define DEBUG_LEVEL t_INFO
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

String get_reset_reason(RESET_REASON reason);
void printBootupInfo();
void Debug(String fileName, String dbgMessage, dbgLevel Type);

#endif
/**********************************end of file**********************************/