/*******************************************************************//**
 * @file    task_man.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief    Provides multi-tasking features with CPU core selection
 * @details  Create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
 *
 *     xTaskCreatePinnedToCore(
 *     Task1code,   Task function.
 *     "Task1",     name of task.
 *     10000,       Stack size of task
 *     NULL,        parameter of the task
 *     1,           priority of the task
 *     &Task1,      Task handle to keep track of created task
 *     0);          pin task to core 0
 **//*********************************************************************/

#include "Arduino.h"
#include "task_man.h"
#include "debug_api.h"
#include "wifi_man.h"
#include "eeprom_crc.h"
#include "timer_man.h"

TaskHandle_t Task1, Task11, Task2;

const char* getTaskName(uint8_t taskId)
{
    char *randName = "tID_0000";
    randName[8] = taskId;
    return randName;
}

void createTasks() 
{
    xTaskCreatePinnedToCore(Task1code, "tID_0001", 10000, NULL, 1, &Task1, 0);
    delay(100);

    xTaskCreatePinnedToCore(Task11code, "tID_0011", 10000, NULL, 1, &Task11, 0);
    delay(100);

    xTaskCreatePinnedToCore(Task2code, "tID_0002", 10000, NULL, 1, &Task2, 1);
    delay(100);
}

// update clock every second
void Task1code(void* pvParameters) 
{
    String taskName = String(pcTaskGetTaskName(pvParameters));
    DEBUG(__FILENAME__, taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

    while (true) 
    {
        vTaskDelay(xDelay);
        DEBUG(__FILENAME__, taskName, t_TRACE);

        Timer.updateLocalTime();
    }
}

// check connection status every minute
void Task11code(void* pvParameters) 
{
    String taskName = String(pcTaskGetTaskName(pvParameters));
    DEBUG(__FILENAME__, taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = 60000 / portTICK_PERIOD_MS;

    while (true) 
    {
        vTaskDelay(xDelay);
        DEBUG(__FILENAME__, taskName, t_TRACE);

        Wifi.checkConection();
    }
}

// autosave eeprom data every 5 minutes
void Task2code(void* pvParameters) 
{
    String taskName = String(pcTaskGetTaskName(pvParameters));
    DEBUG(__FILENAME__, taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = 300000 / portTICK_PERIOD_MS;

    while (true) 
    {
        vTaskDelay(xDelay);
        DEBUG(__FILENAME__, taskName, t_TRACE);

        Eeprom.writeEepromData(&romdata);
    }
}

/**********************************end of file**********************************/