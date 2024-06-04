#include "FreeRTOS.h"
#include "task.h"

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

int main(void) {
    xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);
    vTaskStartScheduler();
    for(;;);
}

void vTask1(void *pvParameters) {
    for (;;) {
        // 다른 작업에게 CPU 양보
        taskYIELD();
    }
}

void vTask2(void *pvParameters) {
    for (;;) {
        // 다른 작업 수행
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
