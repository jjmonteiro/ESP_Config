/*******************************************************************//**
 * @file     debug_api.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief    Debug reporting facility
 * @details  Generic implementation and definitions for the debug facility, 
 *           provided for internal use and code troubleshooting
 * 
**//*********************************************************************/

#ifndef debug_h
#define debug_h
#if defined ESP32
#include <rom/rtc.h>
#define ESP_HEAP_SIZE ESP.getHeapSize()
#else
#define ESP_HEAP_SIZE 54224
#endif

typedef enum dbgLevel {
    t_TRACE,
    t_INFO,
    t_WARN,
    t_ERROR,
    t_FATAL
};

#define DEBUG_LEVEL t_TRACE
#define SERIAL_BAUDRATE	115200
#define TIMESTAMP_BUFFER_SIZE 18
#define ESP_USED_HEAP (ESP_HEAP_SIZE-ESP.getFreeHeap())

#define KB_DIVISOR 1024.0
#define MH_DIVISOR 1000000.0

#define KB " KB"
#define MH " MHz"

#define PRINT(x) Serial.print(x)
#define PRINT_LINE(x) Serial.println(x)

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

void printBootupInfo();
void DEBUG(String fileName, String dbgMessage, dbgLevel Type);

#endif
/**********************************end of file**********************************/