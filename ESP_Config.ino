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

typedef struct eepromData {
    uint32_t  value1;
    uint32_t  value2;
    uint16_t  value3;
    char* ssid = "(-_-)";
    char* psk = "monteiro";
    String    str_1;
    String    str_2;
    String    str_3;
    String    str_4;
};

class eepromManager {

    String dbgName = "eepromManager() ";

private:

    bool isCRCvalid(void) {
        bool isValid;
        uint32_t crc;
        EEPROM.get(0, crc);

        isValid = (crc == getCRC());

        if (isValid) {
            Debug(dbgName + "getCRC() value: " + String(crc), t_OK);
        }
        else {
            Debug(dbgName + "getCRC() check failed.", t_FAIL);
        };
        return isValid;
    }

    uint32_t getCRC() {
        uint32_t crc = ~0L;
        const uint32_t crc_table[16] = {
            0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
            0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
            0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
            0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
        };
        for (int index = sizeof(crc); index < EEPROM_SIZE; ++index) {
            crc = crc_table[(crc ^ EEPROM.read(index)) & 0x0f] ^ (crc >> 4);
            crc = crc_table[(crc ^ (EEPROM.read(index) >> 4)) & 0x0f] ^ (crc >> 4);
            crc = ~crc;
        }
        return (crc);
    }

    void setCRC() {
        uint32_t crc = getCRC();
        EEPROM.put(0, crc);
        if (EEPROM.commit()) {
            Debug(dbgName + "setCRC() value: " + String(crc), t_OK);
        }
        else {
            Debug(dbgName + "setCRC() failed.", t_FAIL);
        };
    }

public:

    void init() {
        EEPROM.begin(EEPROM_SIZE);
    }

    void readEepromData(eepromData* data) {
        if (isCRCvalid()) {
            EEPROM.get(sizeof(uint32_t), *data);
        }
        else {
            Debug(dbgName + "readEepromData() fail, defaults loaded.", t_FAIL);
            writeEepromData(data);
        }
    }

    void writeEepromData(eepromData* data) {

        EEPROM.put(sizeof(uint32_t), *data);

        if (EEPROM.commit()) {
            Debug(dbgName + "writeEepromData() commit success.", t_OK);
            setCRC();
        }
        else {
            Debug(dbgName + "writeEepromData() commit failed.", t_FAIL);
        };

    }


};


//***************************************************//
//Forward object declarations
//***************************************************//

TaskHandle_t Task1, Task11, Task2;
WiFiClient espClient;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // access at ws://[esp ip]/ws

eepromData      mydata;
eepromManager   myeeprom;




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

    myeeprom.init();
    myeeprom.readEepromData(&mydata);

    createTasks();



    wifiManager();

    webManager(spiffsManager());

    //myeeprom.writeEepromData(&mydata);
}


void loop() {


}