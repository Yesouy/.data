#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// 2.18 xTaskGetApplicationTaskTag

#define STACK_SIZE 200
#define TASK_PRIORITY (tskIDLE_PRIORITY + 1)

void vATask(void *pvParameters)
{
    vTaskSetApplicationTaskTag(NULL, (void*)1);
    for(;;)
    {
        
    }
}

void vAFunction(void)
{
    TaskHandle_t xHandle;
    void* pvReturnedTaskTag; 

    if (xTaskCreate(
        vATask,
        "Demo task",
        STACK_SIZE,
        NULL,
        TASK_PRIORITY,
        &xHandle
    ) == pdPASS)
    {
        vTaskDelay(100);

        pvReturnedTaskTag = xTaskGetApplicationTaskTag(xHandle);
        
        printf("Task tag: %ld\n", (long)pvReturnedTaskTag);
    }
}

int main(void)
{
    // Initialize FreeRTOS and create the initial tasks
    vAFunction();

    // Start the scheduler
    vTaskStartScheduler();

    // If all is well, the scheduler will now be running, and the following line will never be reached.
    // If the following line does execute, then there was insufficient FreeRTOS heap memory available for the idle and/or timer tasks to be created.
    for (;;);
}
