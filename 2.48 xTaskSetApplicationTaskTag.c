#include "FreeRTOS.h"
#include "task.h"

void vTaskSetApplicationTaskTag(void *pvParameters)
{
    TaskHandle_t xTask = xTaskGetCurrentTaskHandle();
    vTaskSetApplicationTaskTag(xTask, (TaskHookFunction_t)1);
    printf("Task Tag set to 1\r\n");
}
