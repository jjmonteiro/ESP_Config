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
#include "debug.h"

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
    LOG();
    LOG(separator);
    LOG("Serial Initialized @ " + String(SERIAL_BAUDRATE));
    LOG("EEPROM Size: " + String(EEPROM_SIZE));
    LOG("Reboot reason: ");
    LOG("CPU0: " + get_reset_reason(rtc_get_reset_reason(0)));
    LOG("CPU1: " + get_reset_reason(rtc_get_reset_reason(1)));
    LOG(separator);

    LOG("Chip Rev: " + String(ESP.getChipRevision()));
    LOG("Sdk Ver : " + String(ESP.getSdkVersion()));
    LOG("Cpu Freq: " + String(ESP.getCpuFreqMHz()));
    LOG("Cycles  : " + String(ESP.getCycleCount()));
    LOG(separator);

    LOG("Heap Size  : " + String(ESP.getHeapSize()));
    LOG("Free Heap  : " + String(ESP.getFreeHeap()));
    LOG("SPIRam Size: " + String(ESP.getPsramSize()));
    LOG("SPIRam Free: " + String(ESP.getFreePsram()));
    LOG("Flash Mode : " + String(ESP.getFlashChipMode()));
    LOG("Flash Size : " + String(ESP.getFlashChipSize()));
    LOG("Flash Speed: " + String(ESP.getFlashChipSpeed()));
    LOG(separator);
    LOG(gen_GetVersion());
    LOG(separator);
    LOG();
}

String runTime()
{
    return "00:00:00";
    //unsigned long times = millis();
    //uint8_t millisec = times % 100;
    //uint8_t tseconds = times / 1000;
    //uint8_t tminutes = tseconds / 60;
    //uint8_t seconds = tseconds % 60;
    //return String(tminutes + ":") + String(seconds + ":") + String(millisec);
}

void Debug(String fileName, String dbgMessage, dbgLevel Type) 
{
    if (Type >= DEBUG_LEVEL)
    {
        String msgType;

        switch (Type)
        {
        case t_DEBUG:
            msgType = " DEBUG ";
            break;

        case t_INFO:
            msgType = " INFO  ";
            break;

        case t_WARN:
            msgType = " WARNG ";
            break;

        case t_ERROR:
            msgType = " ERROR ";
            break;

        case t_FATAL:
            msgType = " FATAL ";
            break;

        default:
            break;
        }
        LOG("[" + runTime() + "] " + msgType + fileName + " : " + dbgMessage);
    }
}
//[00:00:00] INFO wifi_man.cpp: Connection successful.
/**********************************end of file**********************************/