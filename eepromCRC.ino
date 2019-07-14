

class EEPROM_CRC {
private:

    bool isCRCvalid(void) {
        uint32_t stored_crc;
        EEPROM.get(0, stored_crc);
        bool result = (stored_crc == getCRC(EEPROM_SIZE));
        if (result) {
            Debug("CRC check OK: " + String(stored_crc), t_INFO);
        }
        else {
            Debug("CRC check failed.", t_FAIL);
        };
        return result;
    }

    uint32_t getCRC(uint16_t total_memory_size) {
        uint32_t crc = ~0L;
        const uint32_t crc_table[16] = {
            0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
            0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
            0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
            0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
        };
        for (int index = sizeof(crc); index < total_memory_size; ++index) {
            crc = crc_table[(crc ^ EEPROM.read(index)) & 0x0f] ^ (crc >> 4);
            crc = crc_table[(crc ^ (EEPROM.read(index) >> 4)) & 0x0f] ^ (crc >> 4);
            crc = ~crc;
        }
        return (crc);
    }

public:

    struct oMemoryData {
        uint32_t	value1 = 0;
        uint32_t	value2 = 0;
        uint16_t	value3 = 0;
        char    	str_1[STRING_LENGTH] = "default";
        char		str_2[STRING_LENGTH] = "default";
        char		str_3[STRING_LENGTH] = "default";
        char		str_4[STRING_LENGTH] = "default";
    }costumerData;

    EEPROM_CRC() { EEPROM.begin(EEPROM_SIZE); }
    ~EEPROM_CRC() {}

    void readEepromData(void) {
        if (isCRCvalid()) {
            EEPROM.get(sizeof(uint32_t), costumerData);
        }
        else {
            Debug("readEepromData: defaults loaded.", t_INFO);
            writeEepromData();
        }
    }

    void writeEepromData(void)
    {
        bool fail = false;
        uint32_t crc;
        EEPROM.put(sizeof(uint32_t), costumerData);
        fail += !EEPROM.commit();
        crc = getCRC(EEPROM_SIZE);
        EEPROM.put(0, crc);
        fail += !EEPROM.commit();
        if (fail) {
            Debug("writeEepromData: Commit failed.", t_FAIL);
        }
        else {
            Debug("writeEepromData: Commit success.", t_INFO);
        };
    }

    void printObjData(void) {
        LOG("++ eeprom data ++");
        LOG(costumerData.value1);
        LOG(costumerData.value2);
        LOG(costumerData.value3);
        LOG(costumerData.str_1);
        LOG(costumerData.str_2);
        LOG(costumerData.str_3);
        LOG(costumerData.str_4);

    }

};






//
//void setup() {
//
//    
//
//
//    system_memory.readEepromData();
//    LOG();
//    LOG("Old EEPROM Data: ");
//    printObjData(system_memory);
//    delay(1000);
//
//    LOG();
//    LOG("New generated data: ");
//    system_memory.costumerData.value1 = random(5000);
//    system_memory.costumerData.value2 = random(1000);
//    system_memory.costumerData.value3 = random(10, 20);
//    strcpy(system_memory.costumerData.str_1, randomStr());
//    strcpy(system_memory.costumerData.str_2, randomStr());
//    strcpy(system_memory.costumerData.str_3, randomStr());
//    strcpy(system_memory.costumerData.str_4, randomStr());
//    printObjData(system_memory);
//    delay(1000);
//
//    LOG();
//    LOG("new data saved!");
//    system_memory.writeEepromData();
//    delay(1000);
//    //ESP.restart();
//}

