#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// 2.24 uxTaskGetStackHighWaterMark

void vTask1(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    printf("Initial high water mark: %u\n", (unsigned int)uxHighWaterMark);

    for (;;)
    {
        vTaskDelay(1000);
        uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        printf("Current high water mark: %u\n", (unsigned int)uxHighWaterMark);
    }
}

int main(void)
{
    xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
    for (;;);
    return 0;
}
