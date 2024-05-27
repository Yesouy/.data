#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// 2.30 pcTaskGetName.c

// 태스크 함수
void vTaskGetName(void *pvParameters)
{
    TaskHandle_t xTask = xTaskGetCurrentTaskHandle();
    const char *pcTaskName = pcTaskGetName(xTask);
    printf("Current Task Name: %s\r\n", pcTaskName);

    for (;;)
    {
        vTaskDelay(1000); // 1초 대기
    }
}

int main(void)
{
    // 태스크 핸들 선언
    TaskHandle_t xTaskHandle;

    // vTaskGetName 태스크 생성
    xTaskCreate(vTaskGetName, "Task 1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &xTaskHandle);

    // FreeRTOS 스케줄러 시작
    vTaskStartScheduler();

    // 스케줄러가 시작되지 않으면 이 코드는 실행됩니다.
    for (;;);

    return 0; // 이 줄은 실행되지 않음
}
