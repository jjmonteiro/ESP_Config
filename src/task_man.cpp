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

#include <Arduino.h>
#ifndef ESP32
#include <Scheduler.h>
#endif
#include "task_man.h"
#include "debug_api.h"
#include "wifi_man.h"
#include "eeprom_crc.h"
#include "timer_man.h"

#define SECOND 1000
#define MINUTE 60*SECOND

#define CLOCK_TASK_TIMER 1
#define WIFI_TASK_TIMER  1*MINUTE
#define SAVE_TASK_TIMER  5*MINUTE

#define CLOCK_TASK_NAME  "t_ID001"
#define WIFI_TASK_NAME   "t_ID002"
#define SAVE_TASK_NAME   "t_ID003"

#ifdef ESP32

#define CPU_CORE_0      0
#define CPU_CORE_1      1
#define TASK_STACK_SIZE 5000
#define TASK_PRIORITY   1

TaskHandle_t Task_1;
TaskHandle_t Task_2;
TaskHandle_t Task_3;

void clock_task(void* pvParameters)
{
    String taskName = String(pcTaskGetTaskName(pvParameters));
    DEBUG(__FILENAME__, taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = CLOCK_TASK_TIMER / portTICK_PERIOD_MS;

    while (true) 
    {
        vTaskDelay(xDelay);
        Timer.updateLocalTime();
        //DEBUG(__FILENAME__, taskName, t_TRACE);
    }
}

void wifi_task(void* pvParameters)
{
    String taskName = String(pcTaskGetTaskName(pvParameters));
    DEBUG(__FILENAME__, taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = WIFI_TASK_TIMER / portTICK_PERIOD_MS;

    while (true) 
    {
        vTaskDelay(xDelay);
        Wifi.checkConection();
        DEBUG(__FILENAME__, taskName, t_TRACE);
    }
}

void save_task(void* pvParameters)
{
    String taskName = String(pcTaskGetTaskName(pvParameters));
    DEBUG(__FILENAME__, taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = SAVE_TASK_TIMER / portTICK_PERIOD_MS;

    while (true) 
    {
        vTaskDelay(xDelay);
        Eeprom.writeEepromData(&romdata);
        DEBUG(__FILENAME__, taskName, t_TRACE);
    }
}

void createTasks()
{
    xTaskCreatePinnedToCore(clock_task, CLOCK_TASK_NAME, TASK_STACK_SIZE, NULL, TASK_PRIORITY, &Task_1, CPU_CORE_0);
    xTaskCreatePinnedToCore(wifi_task,  WIFI_TASK_NAME,  TASK_STACK_SIZE, NULL, TASK_PRIORITY, &Task_2, CPU_CORE_0);
    xTaskCreatePinnedToCore(save_task,  SAVE_TASK_NAME,  TASK_STACK_SIZE, NULL, TASK_PRIORITY, &Task_3, CPU_CORE_1);
}

#else

class t_updateLocalTime : public Task 
{
    int icounter = 0;
    void setup()
    {
        DEBUG(__FILENAME__, String(CLOCK_TASK_NAME) + " started. t=" + String(CLOCK_TASK_TIMER), t_INFO);
    }
    void loop() 
    {
        delay(CLOCK_TASK_TIMER);
        Timer.updateLocalTime();
        icounter++;
        if (icounter > 10 * SECOND)
        {
            DEBUG(__FILENAME__, String(CLOCK_TASK_NAME), t_TRACE);
            icounter = 0;
        }
    }
} clock_task;

class t_checkConnection : public Task 
{
    void setup()
    {
        DEBUG(__FILENAME__, String(WIFI_TASK_NAME) + " started. t=" + String(WIFI_TASK_TIMER), t_INFO);
    }
    void loop() 
    {
        delay(WIFI_TASK_TIMER);
        Wifi.checkConection();
        DEBUG(__FILENAME__, String(WIFI_TASK_NAME), t_TRACE);
    }
} wifi_task;

class t_autoSave : public Task 
{
    void setup()
    {
        DEBUG(__FILENAME__, String(SAVE_TASK_NAME) + " started. t=" + String(SAVE_TASK_TIMER), t_INFO);
    }
    void loop() 
    {
        delay(SAVE_TASK_TIMER);
        Eeprom.writeEepromData(&romdata);
        DEBUG(__FILENAME__, String(SAVE_TASK_NAME), t_TRACE);
    }
} save_task;

void createTasks()
{
    Scheduler.start(&clock_task);
    Scheduler.start(&wifi_task);
    Scheduler.start(&save_task);
    Scheduler.begin();
}

#endif

/**********************************end of file**********************************/