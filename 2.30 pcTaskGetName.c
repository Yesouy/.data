#include "FreeRTOS.h"
#include "task.h"

void vTaskGetName(void *pvParameters)
{
    TaskHandle_t xTask = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTask);
    printf("Current Task Name: %s\r\n", pcTaskName);
}
