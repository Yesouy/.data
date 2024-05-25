#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

// 2.18 xTaskGetApplicationTaskTag

#define STACK_SIZE 200 // 태스크 스택 사이즈, 워드 단위
#define TASK_PRIORITY (tskIDLE_PRIORITY + 1) // 태스크 우선순위

void vATask(void *pvParameters)
{
    vTaskSetApplicationTaskTag(NULL, (void*)1);
    for(;;)
    {
        // 태스크 코드
    }
}

void vAFunction(void)
{
    TaskHandle_t xHandle;
    // TaskHookFunction_t로 반환 타입 변경
    void* pvReturnedTaskTag; 

    // 태스크 생성
    if (xTaskCreate(
        vATask, /* 태스크 함수 */
        "Demo task", /* 태스크 이름 */
        STACK_SIZE, /* 스택 사이즈 */
        NULL, /* 파라미터 */
        TASK_PRIORITY, /* 우선순위 */
        &xHandle /* 태스크 핸들 */
    ) == pdPASS)
    {
        // 태스크가 성공적으로 생성됨
        vTaskDelay(100); // 잠시 대기

        // 태그 값 얻기
        pvReturnedTaskTag = xTaskGetApplicationTaskTag(xHandle);
        
        // 태그 값을 long으로 캐스팅하여 출력 (예제에서는 long으로 캐스팅했으나, 실제 사용 시 타입에 주의하세요)
        printf("Task tag: %ld\n", (long)pvReturnedTaskTag);
    }
}
