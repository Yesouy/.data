#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

TaskHandle_t xTask1Handle = NULL;

void vTask1(void *pvParameters);
void ISR_Handler(void);

int main(void) {
    xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, &xTask1Handle);
    vTaskStartScheduler();
    for(;;);
}

void vTask1(void *pvParameters) {
    uint32_t ulValue;
    for (;;) {
        if (xTaskNotifyWait(0x00, 0xFFFFFFFF, &ulValue, portMAX_DELAY) == pdTRUE) {
            // 알림 값 처리
        }
    }
}

void ISR_Handler(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t ulPreviousNotifyValue;

    xTaskNotifyAndQueryFromISR(xTask1Handle, 0x01, eSetValueWithOverwrite, &ulPreviousNotifyValue, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
