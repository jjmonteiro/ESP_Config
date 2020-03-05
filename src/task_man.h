/*******************************************************************//**
 * @file    task_man.h
 *
 * COPYRIGHT (c) 2020 Joaquim Monteiro
 *
 * @brief    Provides multi-tasking features with CPU core selection
 * @details
 *
 **//*********************************************************************/

#ifndef task_man_h
#define task_man_h

void createTasks();
void Task1code(void* pvParameters);
void Task11code(void* pvParameters);
void Task2code(void* pvParameters);

#endif
/**********************************end of file**********************************/