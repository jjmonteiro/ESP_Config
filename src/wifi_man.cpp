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

//ssid while not connected?
String getSSID() 
{
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    return String(reinterpret_cast<const char*>(conf.sta.ssid));
}

void updateTime()
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

void printAP()
{
    DEBUG(__FILENAME__, "SSID: " + String(romdata.ap_ssid), t_INFO);
    DEBUG(__FILENAME__, "WiFi.softAPIP(): http://" + String(WiFi.softAPIP().toString()), t_INFO);
    DEBUG(__FILENAME__, "WiFi.softAPgetHostname(): http://" + String(WiFi.softAPgetHostname()) + ".mynet", t_INFO);
    DEBUG(__FILENAME__, "WiFi.softAPmacAddress(): " + String(WiFi.softAPmacAddress()), t_INFO);
}

void printSTA()
{
    DEBUG(__FILENAME__, "Connection successful.", t_INFO);
    DEBUG(__FILENAME__, "SSID: " + String(WiFi.SSID()), t_INFO);
    DEBUG(__FILENAME__, "RSSI: " + String(WiFi.RSSI()) + "dBm", t_INFO);
    DEBUG(__FILENAME__, "WiFi.localIP(): http://" + WiFi.localIP().toString(), t_INFO);
    DEBUG(__FILENAME__, "WiFi.getHostname(): http://" + String(WiFi.getHostname()) + ".mynet", t_INFO);
    DEBUG(__FILENAME__, "WiFi.macAddress(): " + String(WiFi.macAddress()), t_INFO);
}

void WiFiEvent(WiFiEvent_t event) 
{
    switch (event)
    {
    case SYSTEM_EVENT_WIFI_READY:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_WIFI_READY", t_INFO);
        //WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE); // IP,GATEWAY,SUBNET
        break;

    case SYSTEM_EVENT_SCAN_DONE:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_SCAN_DONE", t_INFO);
        break;

    case SYSTEM_EVENT_STA_START:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_START", t_INFO);
        break;

    case SYSTEM_EVENT_STA_STOP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_STOP", t_INFO);
        break;

    case SYSTEM_EVENT_STA_CONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_CONNECTED", t_INFO);
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_DISCONNECTED", t_INFO);
        break;

    case SYSTEM_EVENT_STA_AUTHMODE_CHANGE:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_AUTHMODE_CHANGE", t_INFO);
        break;

    case SYSTEM_EVENT_STA_GOT_IP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_GOT_IP", t_INFO);
        break;

    case SYSTEM_EVENT_STA_LOST_IP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_STA_LOST_IP", t_INFO);
        break;

    case SYSTEM_EVENT_AP_START:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_START", t_INFO);
        break;

    case SYSTEM_EVENT_AP_STOP:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STOP", t_INFO);
        break;

    case SYSTEM_EVENT_AP_STACONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STACONNECTED", t_INFO);
        break;

    case SYSTEM_EVENT_AP_STADISCONNECTED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STADISCONNECTED", t_INFO);
        break;

    case SYSTEM_EVENT_AP_STAIPASSIGNED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_STAIPASSIGNED", t_INFO);
        break;

    case SYSTEM_EVENT_AP_PROBEREQRECVED:
        DEBUG(__FILENAME__, "SYSTEM_EVENT_AP_PROBEREQRECVED", t_INFO);
        break;

    default:
        break;
    }
}

void wifiManager() 
{
    if (!WiFi.isConnected() && (WiFi.getMode() == WIFI_MODE_STA))
    {
        WiFi.enableAP(false);
        
        size_t wifi_list_max = sizeof romdata.ssid / sizeof romdata.ssid[0];

        for (size_t index = 0; ((!WiFi.isConnected()) && (index < wifi_list_max)); index++) 
        {
            if (index == 0)
            {
                WiFi.begin();
                DEBUG(__FILENAME__, "Connecting to last known AP", t_INFO);
                WiFi.waitForConnectResult();
            }
            else
            {
                DEBUG(__FILENAME__, "Connecting to list entry #" + String(index), t_INFO);
                WiFi.begin(*romdata.ssid[index], *romdata.psk[index]);
                WiFi.waitForConnectResult();
            }

            if (WiFi.isConnected())
            {
                WiFi.setHostname(romdata.hostname);
                updateTime();
                printSTA();
            }
            else
            {
                DEBUG(__FILENAME__, "Connection failed.", t_ERROR);
            }
        }

        //still not connected! switch to AP?
        if (!WiFi.isConnected()) 
        {
            WiFi.enableSTA(false);
            WiFi.mode(WIFI_MODE_AP);

            WiFi.softAPsetHostname(romdata.hostname);
            WiFi.softAP(romdata.ap_ssid, romdata.ap_psk);
            delay(100);
            printAP();
        }
    }
}

/**********************************end of file**********************************/