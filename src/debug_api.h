/*******************************************************************//**
 * @file    debug.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief   Debugger reporting facility
 * @details Generic implementation and definitions for the debug facility, 
 *          provided for internal use and code troubleshooting
 * 
**//*********************************************************************/

#ifndef debug_h
#define debug_h

typedef enum dbgLevel {
    t_TRACE,
    t_INFO,
    t_WARN,
    t_ERROR,
    t_FATAL
};

#define DEBUG_LEVEL t_INFO
#define SERIAL_BAUDRATE	115200

#define PRINT(x) Serial.print(x)
#define PRINT_LINE(x) Serial.println(x)

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

//String get_reset_reason(RESET_REASON reason);
void printBootupInfo();
void DEBUG(String fileName, String dbgMessage, dbgLevel Type);

#endif
/**********************************end of file**********************************/