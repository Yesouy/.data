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
