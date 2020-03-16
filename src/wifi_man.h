/*******************************************************************//**
 * @file    wifi_man.h
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

#include <WiFi.h>

class wifiManager : public WiFiClass
{
public:
    void init();
    void checkConection();
private:
    void printAP(dbgLevel Type);
    void printSTA(dbgLevel Type);
};

void WiFiEvent(WiFiEvent_t event);
extern wifiManager Wifi;

#endif
/**********************************end of file**********************************/