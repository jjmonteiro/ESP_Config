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

    xTaskCreatePinnedToCore(Task1code,  "Task1",  10000, NULL, 1, &Task1,  0);
    delay(200);
    xTaskCreatePinnedToCore(Task11code, "Task11", 10000, NULL, 1, &Task11, 0);
    delay(200);
    xTaskCreatePinnedToCore(Task2code,  "Task2",  10000, NULL, 1, &Task2,  1);
    delay(200);
}

//Task1code: executes every 1000 ms
void Task1code(void* pvParameters) {
    Debug("Task1 running on core " + String(xPortGetCoreID()), t_INFO);

    while (true) {
        Debug("task_1 on", t_TIME);
        delay(1000);
        Debug("task_1 off", t_TIME);
        delay(1000);
    }
}

//Task1code: blinks an LED every 1000 ms
void Task11code(void* pvParameters) {
    Debug("Task11 running on core " + String(xPortGetCoreID()), t_INFO);

    while (true) {
        Debug("task_11 on", t_TIME);
        delay(5000);
        Debug("task_11 off", t_TIME);
        delay(5000);
    }
}

//Task2code: blinks an LED every 700 ms
void Task2code(void* pvParameters) {
    Debug("Task2 running on core " + String(xPortGetCoreID()), t_INFO);

    while (true) {
        Debug("task_2 on", t_TIME);
        delay(2000);
        Debug("task_2 off", t_TIME);
        delay(2000);
    }
}