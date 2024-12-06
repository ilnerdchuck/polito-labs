#pragma once
#include <stdint.h>
#include <FreeRTOS.h>
#include "portable.h"
#include "portmacro.h"
#include "projdefs.h"
#include "u_task.h"

typedef struct{
  TaskFunction_t TaskCallback;
  char *TaskName;
  configSTACK_DEPTH_TYPE StackSize;
  void *Parameters;
  UBaseType_t Prio;
  TaskHandle_t TaskHandler;
} taskInfo;


int initDoggy(int);
//Function to register a task to the watchdog
int TaskDoggyRegister(taskInfo);
//Function to send a notification to the watchdog
int DoggySendAlive(int);
//Funciton to remove a task from the watchdog
int TaskDoggyRemove(TaskHandle_t);

