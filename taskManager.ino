//***************************************************//
//Module:   taskManager
//Created:  08-Nov-18 12:44:00
//Author:   Joaquim Monteiro
//Brief:    Provides multi-tasking features with CPU core selection
//
//Usage:
//    create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
//    xTaskCreatePinnedToCore(
//      Task1code,   /* Task function. */
//      "Task1",     /* name of task. */
//      10000,       /* Stack size of task */
//      NULL,        /* parameter of the task */
//      1,           /* priority of the task */
//      &Task1,      /* Task handle to keep track of created task */
//      0);          /* pin task to core 0 */
//***************************************************//


void createTasks() { 

    xTaskCreatePinnedToCore(Task1code, "tID_0001",  10000, NULL, 1, &Task1,  0);
    delay(100);

    xTaskCreatePinnedToCore(Task11code, "tID_0011", 10000, NULL, 1, &Task11, 0);
    delay(100);

    xTaskCreatePinnedToCore(Task2code, "tID_0002",  10000, NULL, 1, &Task2,  1);
    delay(100);
}


void Task1code(void* pvParameters) {
    String taskName = String(pcTaskGetTaskName(pvParameters));
    Debug(taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

    while (true) {
        Debug(taskName, t_TIME);
        vTaskDelay(xDelay);
    }
}


void Task11code(void* pvParameters) {
    String taskName = String(pcTaskGetTaskName(pvParameters));
    Debug(taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = 5000 / portTICK_PERIOD_MS;

    while (true) {
        Debug(taskName, t_TIME);
        wifiManager();
        vTaskDelay(xDelay);
    }
}


void Task2code(void* pvParameters) {
    String taskName = String(pcTaskGetTaskName(pvParameters));
    Debug(taskName + " started on CPU_" + String(xPortGetCoreID()), t_INFO);
    const TickType_t xDelay = 2000 / portTICK_PERIOD_MS;

    while (true) {
        Debug(taskName, t_TIME);
        vTaskDelay(xDelay);
    }
}