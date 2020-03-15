/*******************************************************************//**
 * @file    wifi_man.cpp
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
#include "time.h"

extern eepromData romdata;
extern struct tm* timeinfo;
wifiManager Wifi;

void wifiManager::init()
{
    //WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE); // IP,GATEWAY,SUBNET
    (DEBUG_LEVEL == t_TRACE) ? Wifi.onEvent(WiFiEvent) : 0;
    Wifi.mode(WIFI_MODE_STA);
    Wifi.checkConection();
}

void wifiManager::updateTime()
{
    configTime(romdata.gmtOffset_sec, romdata.daylightOffset_sec, romdata.ntpServer);
    if (!getLocalTime(timeinfo)) {
        DEBUG(__FILENAME__, "NTP clock update failed.", t_ERROR);
    }
    else
    {
        DEBUG(__FILENAME__, "NTP clock updated.", t_INFO);
    }
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

void WiFiEvent(WiFiEvent_t event)
{
    switch (event)
    {
    case SYSTEM_EVENT_WIFI_READY:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_WIFI_READY", t_TRACE);
        break;

    case SYSTEM_EVENT_SCAN_DONE:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_SCAN_DONE", t_TRACE);
        break;

    case SYSTEM_EVENT_STA_START:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_START", t_TRACE);
        break;

    case SYSTEM_EVENT_STA_STOP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_STOP", t_TRACE);
        break;

    case SYSTEM_EVENT_STA_CONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_CONNECTED", t_TRACE);
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_DISCONNECTED", t_TRACE);
        break;

    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_AUTHMODE_CHANGE", t_TRACE);
        break;

    case SYSTEM_EVENT_STA_GOT_IP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_GOT_IP", t_TRACE);
        break;

    case SYSTEM_EVENT_STA_LOST_IP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_LOST_IP", t_TRACE);
        break;

    case SYSTEM_EVENT_AP_START:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_START", t_TRACE);
        break;

    case SYSTEM_EVENT_AP_STOP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STOP", t_TRACE);
        break;

    case SYSTEM_EVENT_AP_STACONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STACONNECTED", t_TRACE);
        break;

    case SYSTEM_EVENT_AP_STADISCONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STADISCONNECTED", t_TRACE);
        break;

    case SYSTEM_EVENT_AP_STAIPASSIGNED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STAIPASSIGNED", t_TRACE);
        break;

    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_PROBEREQRECVED", t_TRACE);
        break;

    default:
        break;
    }
}

void wifiManager::checkConection()
{
    if (!Wifi.isConnected())
    {
        //WiFi.enableAP(false);
        //WiFi.mode(WIFI_MODE_STA);
        //size_t wifi_list_max = sizeof romdata.ssid / sizeof romdata.ssid[0];

        //for (size_t index = 0; ((!WiFi.isConnected()) && (index < wifi_list_max)); index++) 
        {
            //if (index == 0)
            {
                DEBUG(__FILENAME__, "Connecting to last known AP", t_INFO);
                Wifi.begin();
                Wifi.waitForConnectResult();
            }
            //else
            //{
            //    DEBUG(__FILENAME__, "Connecting to list entry #" + String(index), t_INFO);
            //    WiFi.begin(*romdata.ssid[index], *romdata.psk[index]);
            //    WiFi.waitForConnectResult();
            //}

            if (Wifi.isConnected())
            {
                Wifi.setHostname(romdata.hostname);
                printSTA(t_INFO);
                updateTime();
            }
            else
            {
                DEBUG(__FILENAME__, "Connection failed.", t_ERROR);
            }
        }

        //still not connected! switch to AP?
        if (!Wifi.isConnected()) 
        {
            DEBUG(__FILENAME__, "Starting access point mode.", t_INFO);
            //WiFi.enableSTA(false);
            Wifi.mode(WIFI_MODE_AP);

            Wifi.softAPsetHostname(romdata.hostname);
            Wifi.softAP(romdata.ap_ssid, romdata.ap_psk);
            delay(100);
            printAP(t_INFO);
        }
    }
}

/**********************************end of file**********************************/