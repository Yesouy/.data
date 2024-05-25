#include "FreeRTOS.h"
#include "task.h"

void vTaskYield(void *pvParameters)
{
    for (;;)
    {
        printf("Task Yield Example\r\n");
        taskYIELD(); // 다른 태스크에게 CPU 제어권 양도
    }
}
