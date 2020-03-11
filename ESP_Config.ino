/*******************************************************************//**
 * @file    ESP_Config.ino
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 **//*********************************************************************/

#include "Arduino.h"
#include "SPIFFS.h"
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "AsyncWebSocket.h"
#include <ArduinoJson.h>
#include <time.h>

#include "src/version.h"
#include "src/debug_api.h"
#include "src/eeprom_crc.h"
//#include "src/shell.h"
#include "src/spiffs_man.h"
#include "src/wifi_man.h"
#include "src/task_man.h"
#include "src/web_socket.h"
#include "src/web_man.h"

extern eepromManager eeprom;
extern eepromData romdata;

void setup() 
{
    Serial.begin(SERIAL_BAUDRATE);
    printBootupInfo();

    eeprom.init();
    eeprom.readEepromData(&romdata);

    WiFi.enableSTA(true);
    WiFi.mode(WIFI_MODE_STA);
    WiFi.onEvent(WiFiEvent);

    webManager(spiffsManager()); 
    createTasks();
}


void loop() 
{
    yield();
}

