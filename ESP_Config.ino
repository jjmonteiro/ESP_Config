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

#include "src/version.h"
#include "src/debug_api.h"
#include "src/eeprom_crc.h"
//#include "src/shell.h"
#include "src/spiffs_man.h"
#include "src/task_man.h"
#include "src/wifi_man.h"
#include "src/web_socket.h"
#include "src/web_man.h"

extern eepromManager eeprom;
extern eepromData romdata;

void setup() 
{
    Serial.begin(SERIAL_BAUDRATE);
    WiFi.mode(WIFI_MODE_STA);
    WiFi.setAutoConnect(false);
    WiFi.setAutoReconnect(false);

    printBootupInfo();
    eeprom.init();
    eeprom.readEepromData(&romdata);
    
    createTasks();

    WiFi.onEvent(WiFiEvent);
    
    webManager(spiffsManager());

    eeprom.writeEepromData(&romdata);
}


void loop() 
{
    wifiManager();
    delay(5000);
}



//String PtrToString(uint8_t* str, unsigned int len) {
//    String result;
//    for (int i = 0; i < len; i++) {
//        result += ((char)str[i]);
//    }
//    return result;
//}
