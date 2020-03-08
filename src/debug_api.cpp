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

#include "Arduino.h"
#include "debug_api.h"
#include <rom/rtc.h>
#include "eeprom_crc.h"
#include "version.h"
#include <string.h>
#include "time.h"

time_t rawtime;
struct tm* timeinfo = localtime(&rawtime);

String get_reset_reason(RESET_REASON reason)
{
    switch (reason)
    {
    case 1: return("POWERON_RESET"); break;          /**<1, Vbat power on reset*/
    case 3: return("SW_RESET"); break;               /**<3, Software reset digital core*/
    case 4: return("OWDT_RESET"); break;             /**<4, Legacy watch dog reset digital core*/
    case 5: return("DEEPSLEEP_RESET"); break;        /**<5, Deep Sleep reset digital core*/
    case 6: return("SDIO_RESET"); break;             /**<6, Reset by SLC module, reset digital core*/
    case 7: return("TG0WDT_SYS_RESET"); break;       /**<7, Timer Group0 Watch dog reset digital core*/
    case 8: return("TG1WDT_SYS_RESET"); break;       /**<8, Timer Group1 Watch dog reset digital core*/
    case 9: return("RTCWDT_SYS_RESET"); break;       /**<9, RTC Watch dog Reset digital core*/
    case 10: return("INTRUSION_RESET"); break;       /**<10, Instrusion tested to reset CPU*/
    case 11: return("TGWDT_CPU_RESET"); break;       /**<11, Time Group reset CPU*/
    case 12: return("SW_CPU_RESET"); break;          /**<12, Software reset CPU*/
    case 13: return("RTCWDT_CPU_RESET"); break;      /**<13, RTC Watch dog Reset CPU*/
    case 14: return("EXT_CPU_RESET"); break;         /**<14, for APP CPU, reseted by PRO CPU*/
    case 15: return("RTCWDT_BROWN_OUT_RESET"); break;/**<15, Reset when the vdd voltage is not stable*/
    case 16: return("RTCWDT_RTC_RESET"); break;      /**<16, RTC Watch dog reset digital core and rtc module*/
    default: return("NO_MEAN");
    }
}

void printBootupInfo() {
    String separator = "--------------------------";
    PRINT_LINE();
    PRINT_LINE(separator);
    PRINT_LINE("Serial Initialized @ " + String(SERIAL_BAUDRATE));
    PRINT_LINE("EEPROM Size: " + String(EEPROM_SIZE));
    PRINT_LINE("Reboot reason: ");
    PRINT_LINE("CPU0: " + get_reset_reason(rtc_get_reset_reason(0)));
    PRINT_LINE("CPU1: " + get_reset_reason(rtc_get_reset_reason(1)));
    PRINT_LINE(separator);

    PRINT_LINE("Chip Rev: " + String(ESP.getChipRevision()));
    PRINT_LINE("Sdk Ver : " + String(ESP.getSdkVersion()));
    PRINT_LINE("Cpu Freq: " + String(ESP.getCpuFreqMHz()));
    PRINT_LINE("Cycles  : " + String(ESP.getCycleCount()));
    PRINT_LINE(separator);

    PRINT_LINE("Heap Size  : " + String(ESP.getHeapSize()));
    PRINT_LINE("Free Heap  : " + String(ESP.getFreeHeap()));
    PRINT_LINE("SPIRam Size: " + String(ESP.getPsramSize()));
    PRINT_LINE("SPIRam Free: " + String(ESP.getFreePsram()));
    PRINT_LINE("Flash Mode : " + String(ESP.getFlashChipMode()));
    PRINT_LINE("Flash Size : " + String(ESP.getFlashChipSize()));
    PRINT_LINE("Flash Speed: " + String(ESP.getFlashChipSpeed()));
    PRINT_LINE(separator);
    PRINT_LINE(gen_GetVersion());
    PRINT_LINE(separator);
    PRINT_LINE();
}

// is called every second
String timestamp(tm *timedata)
{
    //Serial.print(timeinfo, "%g:%j-%X"); //[YY:DDD-00:00:00]

    char buffer[80];
    strftime(buffer, 80, "[%g:%j-%X]", timedata);
    //String buffer = "[YY:DDD-00:00:00]";
    return String(buffer);
}

void DEBUG(String fileName, String dbgMessage, dbgLevel Type) 
{
    if (Type >= DEBUG_LEVEL)
    {
        String msgType;

        switch (Type)
        {
        case t_TRACE:
            msgType = "[ TRACE ]";
            break;

        case t_INFO:
            msgType = "[ INFO ]";
            break;

        case t_WARN:
            msgType = "[ WARNG ]";
            break;

        case t_ERROR:
            msgType = "[ ERROR ]";
            break;

        case t_FATAL:
            msgType = "[ FATAL ]";
            break;

        default:
            break;
        }

        PRINT_LINE(timestamp(timeinfo) + msgType + " " + fileName + " : " + dbgMessage);
    }
}

/**********************************end of file**********************************/