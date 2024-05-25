#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// 2.12 taskDISABLE_INTERRUPTS

void vTaskExample(void *pvParameters)
{
    for (;;)
    {
        taskDISABLE_INTERRUPTS();
        
        printf("Critical section: Interrupts disabled\r\n");
        
        taskENABLE_INTERRUPTS();
        
        printf("Non-critical section\r\n");
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    xTaskCreate(vTaskExample, "TaskExample", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler();

    for (;;);
}