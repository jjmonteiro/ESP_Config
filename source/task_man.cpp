/*******************************************************************//**
 * @file    task_man.cpp
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief    Provides multi-tasking features with CPU core selection
 * @details
 * @example  Create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
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
#include "debug.h"

TaskHandle_t    Task1, Task11, Task2;

const char* getTaskName(uint8_t taskId)
{
    char *randName = "tID_0000";
    randName[8] = taskId;
    return randName;
}

void createTasks() {

    xTaskCreatePinnedToCore(Task1code, getTaskName(1), 10000, NULL, 1, &Task1, 0);
    delay(100);

    xTaskCreatePinnedToCore(Task11code, getTaskName(2), 10000, NULL, 1, &Task11, 0);
    delay(100);

    xTaskCreatePinnedToCore(Task2code, getTaskName(3), 10000, NULL, 1, &Task2, 1);
    delay(100);
}

void Task1code(void* pvParameters) {
    String taskName = String(pcTaskGetTaskName(pvParameters));
    Debug(__FILENAME__, taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

    while (true) {
        Debug(__FILENAME__, taskName, t_INFO);
        vTaskDelay(xDelay);
    }
}


void Task11code(void* pvParameters) {
    String taskName = String(pcTaskGetTaskName(pvParameters));
    Debug(__FILENAME__, taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = 5000 / portTICK_PERIOD_MS;

    while (true) {
        Debug(__FILENAME__, taskName, t_INFO);

        vTaskDelay(xDelay);
    }
}


void Task2code(void* pvParameters) {
    String taskName = String(pcTaskGetTaskName(pvParameters));
    Debug(__FILENAME__, taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = 2000 / portTICK_PERIOD_MS;

    while (true) {
        Debug(__FILENAME__, taskName, t_INFO);
        vTaskDelay(xDelay);
    }
}

/**********************************end of file**********************************/