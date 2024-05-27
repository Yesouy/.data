#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// 2.24 uxTaskGetStackHighWaterMark

void vTask1(void *pvParameters)
{
    UBaseType_t uxHighWaterMark;

    // 태스크가 시작될 때 호출하는 태스크의 스택 여유 공간을 검사합니다.
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);

    // 초기 스택 여유 공간을 출력합니다.
    printf("Initial high water mark: %u\n", (unsigned int)uxHighWaterMark);

    for (;;)
    {
        // 1초 지연
        vTaskDelay(1000);

        // 함수 호출 후의 스택 여유 공간을 다시 검사합니다.
        uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);

        // 현재 스택 여유 공간을 출력합니다.
        printf("Current high water mark: %u\n", (unsigned int)uxHighWaterMark);
    }
}

int main(void)
{
    // 태스크 핸들 선언
    TaskHandle_t xTaskHandle;

    // vTask1 태스크 생성
    xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &xTaskHandle);

    // FreeRTOS 스케줄러 시작
    vTaskStartScheduler();

    // 스케줄러가 시작되지 않으면 이 코드는 실행됩니다.
    // 이 경우, 시스템에 충분한 메모리가 없음을 의미합니다.
    for (;;);

    return 0; // 이 줄은 실행되지 않음
}
