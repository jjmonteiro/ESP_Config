/*******************************************************************//**
 * @file     wifi_man.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief   
 * @details  
 *
 *
 **//*********************************************************************/

#ifndef wifi_man_h
#define wifi_man_h

#if defined ESP32

#include <WiFi.h>
class wifiManager : public WiFiClass
{
public:
    void init();
    void checkConection();
    String getEncriptionType(uint8_t network_item);
private:
    void printAP(dbgLevel Type);
    void printSTA(dbgLevel Type);
};

#else

#include <ESP8266WiFi.h>
// WIFI_OFF = 0, WIFI_STA = 1, WIFI_AP = 2, WIFI_AP_STA = 3
#define WIFI_MODE_STA WIFI_STA
#define WIFI_MODE_AP WIFI_AP
#define softAPgetHostname() softAPSSID()
#define getHostname() hostname()
#define setHostname(x) hostname(x)
#define softAPsetHostname(x) softAPSSID(x)

typedef enum
{
    WIFI_AUTH_OPEN = 0,         /**< authenticate mode : open */
    WIFI_AUTH_WEP,              /**< authenticate mode : WEP */
    WIFI_AUTH_WPA_PSK,          /**< authenticate mode : WPA_PSK */
    WIFI_AUTH_WPA2_PSK,         /**< authenticate mode : WPA2_PSK */
    WIFI_AUTH_WPA_WPA2_PSK,     /**< authenticate mode : WPA_WPA2_PSK */
    WIFI_AUTH_WPA2_ENTERPRISE,  /**< authenticate mode : WPA2_ENTERPRISE */
    WIFI_AUTH_WPA3_PSK,         /**< authenticate mode : WPA3_PSK */
    WIFI_AUTH_MAX
} wifi_auth_mode_t;

class wifiManager : public ESP8266WiFiClass
{
public:
    void init();
    void checkConection();
    String getEncriptionType(uint8_t network_item);
private:
    void printAP(dbgLevel Type);
    void printSTA(dbgLevel Type);
};

#endif

extern class wifiManager Wifi;

#endif
/**********************************end of file**********************************/