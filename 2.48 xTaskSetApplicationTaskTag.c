#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t xTask1Handle = NULL;

void vTask1(void *pvParameters);

int main(void) {
    xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, &xTask1Handle);

    // 태그 설정
    vTaskSetApplicationTaskTag(xTask1Handle, (void *)1);

    vTaskStartScheduler();
    for(;;);
}

void vTask1(void *pvParameters) {
    for (;;) {
        // 태그 값 읽기
        void *tag = pvTaskGetApplicationTaskTag(NULL);
        // 태그 값 처리
    }
}
