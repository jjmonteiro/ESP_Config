/*******************************************************************//**
 * @file     wifi_man.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details  
 *
 *
 **//*********************************************************************/

#include "Arduino.h"
#include "debug_api.h"
#include "wifi_man.h"
#include "eeprom_crc.h"
#include "timer_man.h"

wifiManager Wifi;
extern eepromData romdata;

void WiFiEvent(WiFiEvent_t event)
{
    const dbgLevel cn_EventLevel = t_INFO;
    switch (event)
    {
    case SYSTEM_EVENT_WIFI_READY:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_WIFI_READY", cn_EventLevel);
        break;

    case SYSTEM_EVENT_SCAN_DONE:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_SCAN_DONE", cn_EventLevel);
        break;

    case SYSTEM_EVENT_STA_START:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_START", cn_EventLevel);
        break;

    case SYSTEM_EVENT_STA_STOP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_STOP", cn_EventLevel);
        break;

    case SYSTEM_EVENT_STA_CONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_CONNECTED", cn_EventLevel);
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_DISCONNECTED", cn_EventLevel);
        break;

    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_AUTHMODE_CHANGE", cn_EventLevel);
        break;

    case SYSTEM_EVENT_STA_GOT_IP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_GOT_IP", cn_EventLevel);
        break;

    case SYSTEM_EVENT_STA_LOST_IP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_LOST_IP", cn_EventLevel);
        break;

    case SYSTEM_EVENT_AP_START:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_START", cn_EventLevel);
        break;

    case SYSTEM_EVENT_AP_STOP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STOP", cn_EventLevel);
        break;

    case SYSTEM_EVENT_AP_STACONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STACONNECTED", cn_EventLevel);
        break;

    case SYSTEM_EVENT_AP_STADISCONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STADISCONNECTED", cn_EventLevel);
        break;

    case SYSTEM_EVENT_AP_STAIPASSIGNED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STAIPASSIGNED", cn_EventLevel);
        break;

    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_PROBEREQRECVED", cn_EventLevel);
        break;

    default:
        break;
    }
}

void wifiManager::init()
{
    //WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE); // IP,GATEWAY,SUBNET
    Wifi.onEvent(WiFiEvent);
    Wifi.mode(WIFI_MODE_STA);
    Wifi.checkConection();
}

void wifiManager::printAP(dbgLevel Type)
{
    if (DEBUG_LEVEL <= Type)
    {

        PRINT_LINE("   SSID: " + String(romdata.ap_ssid));
        PRINT_LINE("   WiFi.softAPIP(): http://" + String(Wifi.softAPIP().toString()));
        PRINT_LINE("   WiFi.softAPgetHostname(): http://" + String(Wifi.softAPgetHostname()) + ".mynet");
        PRINT_LINE("   WiFi.softAPmacAddress(): " + String(Wifi.softAPmacAddress()));
    }
}

void wifiManager::printSTA(dbgLevel Type)
{
    if (DEBUG_LEVEL <= Type)
    {
        PRINT_LINE("   SSID: " + String(Wifi.SSID()));
        PRINT_LINE("   RSSI: " + String(Wifi.RSSI()) + "dBm");
        PRINT_LINE("   WiFi.localIP(): http://" + Wifi.localIP().toString());
        PRINT_LINE("   WiFi.getHostname(): http://" + String(Wifi.getHostname()) + ".mynet");
        PRINT_LINE("   WiFi.macAddress(): " + String(Wifi.macAddress()));
    }
}

void wifiManager::checkConection()
{
    if (!Wifi.isConnected() && Wifi.mode(WIFI_MODE_STA))
    {
        if (!Wifi.isConnected())
        {
            DEBUG(__FILENAME__, "Connecting to last known AP", t_INFO);
            Wifi.begin();
            Wifi.waitForConnectResult();
        }

        //if (!Wifi.isConnected())
        //{
        //    DEBUG(__FILENAME__, "Connecting to saved AP: " + String(romdata.sta_ssid), t_INFO);
        //    Wifi.begin(romdata.sta_ssid, romdata.sta_psk);
        //    Wifi.waitForConnectResult();
        //}

        if (Wifi.isConnected())
        {
            Wifi.setHostname(romdata.hostname);
            printSTA(t_INFO);
            Timer.updateNTP(romdata.gmtOffset_sec, romdata.dstOffset_sec, romdata.ntpServer);
            Wifi.SSID().toCharArray(romdata.sta_ssid, Wifi.SSID().length()+1);
            Wifi.psk().toCharArray(romdata.sta_psk, Wifi.psk().length()+1);
        }
        else
        {
            DEBUG(__FILENAME__, "Connection failed.", t_ERROR);
            WiFi.disconnect(true);
            WiFi.mode(WIFI_OFF);
        }

        // still not connected! switch to AP.
        if (!Wifi.isConnected()) 
        {
            DEBUG(__FILENAME__, "Starting access point mode.", t_INFO);
            Wifi.mode(WIFI_MODE_AP);
            Wifi.softAPsetHostname(romdata.hostname);
            Wifi.softAP(romdata.ap_ssid, romdata.ap_psk);
            printAP(t_INFO);
        }
    }
}

/**********************************end of file**********************************/