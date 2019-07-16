//***************************************************//
//Created:   08-Nov-18 12:44:00
//Author:    Joaquim Monteiro
//Brief: 
//***************************************************//

#include <EEPROM.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

#include "FS.h"
#include "SPIFFS.h"
#include <rom/rtc.h>

//***************************************************//
//Global variables
//***************************************************//
#define SW_VERSION_MAJOR    1
#define SW_VERSION_MINOR    10
#define HW_REVISION         1


#define STRING_LENGTH   24
#define SLEEP_PERIOD	30e6	//20 seconds
#define SHUTDOWN_TIMEOUT 500
#define TASK_RUN_TWICE 2
#define BUILTIN_LED		2
#define SERIAL_BAUDRATE	115200
#define EEPROM_SIZE 512

#define LOG(x) Serial.println(x)
enum debugTypes {
    t_TIME,
    t_INFO,
    t_WARN,
    t_ERROR,
    t_OK,
    t_FAIL
};





const char* ssid = "(-_-)";
const char* psk = "monteiro";
//***************************************************//






//***************************************************//
//Forward object declarations
//***************************************************//

TaskHandle_t Task1, Task11, Task2;


WiFiClient espClient;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // access at ws://[esp ip]/ws

//EEPROM_CRC system_memory;
//***************************************************//



String PtrToString(uint8_t* str, unsigned int len) {
    String result;
    for (int i = 0; i < len; i++) {
        result += ((char)str[i]);
    }
    return result;
}


void setup() {
    Serial.begin(SERIAL_BAUDRATE);
    printBootupInfo();
    createTasks();



    wifiManager();

    webManager(spiffsManager());


}


void loop() {


}