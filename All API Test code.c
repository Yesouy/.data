#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// 태스크 핸들러 선언
TaskHandle_t xTask1Handle = NULL;
TaskHandle_t xTask2Handle = NULL;

// 애플리케이션 태스크 태그를 위한 변수
UBaseType_t uxTaskTag = 1;

// ISR에서 호출될 함수
void vApplicationTickHook(void)
{
    static BaseType_t xHigherPriorityTaskWoken;
    static uint32_t ulCount = 0;

    // 1000틱마다 xTask1Handle에 알림을 보냄
    ulCount++;
    if (ulCount >= 1000)
    {
        ulCount = 0;
        uint32_t ulPreviousNotificationValue;
        xTaskNotifyAndQueryFromISR(xTask1Handle, 1, eSetValueWithOverwrite, &ulPreviousNotificationValue, &xHigherPriorityTaskWoken);

        // ISR에서 애플리케이션 태스크 태그 얻기
        void *pvTaskTag = xTaskGetApplicationTaskTagFromISR(xTask1Handle);
        printf("ISR: Task 1 Tag: %d\n", (int)pvTaskTag);
    }
}

// 태스크 함수
void vTask1(void *pvParameters)
{
    uint32_t ulNotificationValue;
    while (1)
    {
        // 알림을 기다림
        xTaskNotifyWait(0x00, 0xFFFFFFFF, &ulNotificationValue, portMAX_DELAY);

        // 애플리케이션 태스크 태그 얻기
        void *pvTaskTag = xTaskGetApplicationTaskTag(NULL);
        printf("Task 1 Notified with value: %d, Task Tag: %d\n", ulNotificationValue, (int)pvTaskTag);

        // 스택 여유 공간 확인
        UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        printf("Task 1 High Water Mark: %d\n", uxHighWaterMark);

        // 태스크 이름 출력
        printf("Task 1 Name: %s\n", pcTaskGetName(NULL));

        // 1초 대기
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTask2(void *pvParameters)
{
    while (1)
    {
        // 모든 태스크의 스케줄링 일시 중지
        vTaskSuspendAll();

        // Task 1에게 알림 보내기
        xTaskNotify(xTask1Handle, (1 << 0), eSetBits);

        // 태스크 스케줄링 재개
        xTaskResumeAll();

        // 태스크 yield
        taskYIELD();

        // 1초 대기
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    // 인터럽트 비활성화
    taskDISABLE_INTERRUPTS();

    // Task 1 생성
    xTaskCreate(vTask1, "Task 1", 2048, NULL, 1, &xTask1Handle);

    // Task 2 생성
    xTaskCreate(vTask2, "Task 2", 2048, NULL, 1, &xTask2Handle);

    // Task 1에 애플리케이션 태스크 태그 설정
    vTaskSetApplicationTaskTag(xTask1Handle, (void *)uxTaskTag);

    // 인터럽트 활성화
    taskENABLE_INTERRUPTS();

    // 태스크 스케줄러 시작
    vTaskStartScheduler();

    // 메인 루프
    while (1)
    {
    }

    return 0;
}
