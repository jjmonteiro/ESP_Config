/*******************************************************************//**
 * @file     ESP_Config.ino
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief
 * @details
 *
 **//*********************************************************************/

#define ESP32  // board selector: ESP32 or ESP01

#if defined ESP32
#include <WiFi.h>
#include <SPIFFS.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <FS.h>
#include <LittleFS.h>
#include <Scheduler.h>
#endif
#include <Arduino.h>
#include <EEPROM.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h>
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
#include "src/timer_man.h"

void setup() 
{
    Serial.begin(SERIAL_BAUDRATE);
    printBootupInfo();

    Timer.init();
    Eeprom.init();
    Wifi.init();
    FileSystem.init();

    webManager(); 
    createTasks();
}

void loop() 
{
    yield();
}

