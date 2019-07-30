//***************************************************//
//Created:   08-Nov-18 12:44:00
//Author:    Joaquim Monteiro
//Brief: 
//***************************************************//


#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "FS.h"
#include "SPIFFS.h"
#include "eepromCRC.h"
#include <rom/rtc.h>

//***************************************************//
//Globals
//***************************************************//
#define SW_VERSION_MAJOR    1
#define SW_VERSION_MINOR    10
#define HW_REVISION         1

#define SERIAL_BAUDRATE	115200
#define LOG(x) Serial.println(x)
typedef enum debugTypes {
    t_TIME,
    t_INFO,
    t_WARN,
    t_ERROR,
    t_OK,
    t_FAIL
};

struct eepromData {
    uint32_t    value1 = 0;
    uint32_t    value2 = 0;
    uint16_t    value3 = 0;
    char*       hostname = "esp32";
    char*       ssid[5][32] = { {"","","","",""} };
    char*       psk[5][32] = { {"","","","",""} };
    char*       ap_ssid = "esp32-123";
    char*       ap_psk = "12345678";
    String      str_1 = "";
    String      str_2 = "";
    String      str_3 = "";
}mydata;

//*************************************************//

TaskHandle_t    Task1, Task11, Task2;
eepromManager   myeeprom;
AsyncWebServer  server(80);
AsyncWebSocket  ws("/ws");


void setup() {

    Serial.begin(SERIAL_BAUDRATE);
    printBootupInfo();

    myeeprom.init();
    myeeprom.readEepromData(&mydata);
    
    createTasks();

    WiFi.onEvent(WiFiEvent);

    WiFi.mode(WIFI_MODE_APSTA);
    
    webManager(spiffsManager());

    //myeeprom.writeEepromData(&mydata);
}


void loop() {


}



//String PtrToString(uint8_t* str, unsigned int len) {
//    String result;
//    for (int i = 0; i < len; i++) {
//        result += ((char)str[i]);
//    }
//    return result;
//}