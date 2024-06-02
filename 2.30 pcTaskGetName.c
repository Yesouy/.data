#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// 2.30 pcTaskGetName.c

void vTaskGetName(void *pvParameters)
{
    TaskHandle_t xTask = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTask);
    printf("Current Task Name: %s\r\n", pcTaskName);

    for (;;)
    {
        vTaskDelay(1000);
    }
}

int main(void)
{
    TaskHandle_t xTaskHandle;

    xTaskCreate(vTaskGetName, "Task 1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &xTaskHandle);

    vTaskStartScheduler();

    for (;;);

    return 0;
}
