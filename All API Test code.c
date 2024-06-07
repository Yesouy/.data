#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

TaskHandle_t xTask1Handle = NULL;
TaskHandle_t xTask2Handle = NULL;

UBaseType_t uxTaskTag = 1;

void vApplicationTickHook(void)
{
    static BaseType_t xHigherPriorityTaskWoken;
    static uint32_t ulCount = 0;

    ulCount++;
    if (ulCount >= 1000)
    {
        ulCount = 0;
        uint32_t ulPreviousNotificationValue;
        xTaskNotifyAndQueryFromISR(xTask1Handle, 1, eSetValueWithOverwrite, &ulPreviousNotificationValue, &xHigherPriorityTaskWoken);

        void *pvTaskTag = xTaskGetApplicationTaskTagFromISR(xTask1Handle);
        printf("ISR: Task 1 Tag: %d\n", (int)pvTaskTag);
    }
}

void vTask1(void *pvParameters)
{
    uint32_t ulNotificationValue;
    while (1)
    {
        xTaskNotifyWait(0x00, 0xFFFFFFFF, &ulNotificationValue, portMAX_DELAY);

        void *pvTaskTag = xTaskGetApplicationTaskTagFromISR(NULL);
        printf("Task 1 Notified with value: %d, Task Tag: %d\n", ulNotificationValue, (int)pvTaskTag);

        UBaseType_t uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
        printf("Task 1 High Water Mark: %d\n", uxHighWaterMark);

        printf("Task 1 Name: %s\n", pcTaskGetName(NULL));

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vTask2(void *pvParameters)
{
    while (1)
    {
        vTaskSuspendAll();

        xTaskNotify(xTask1Handle, (1 << 0), eSetBits);

        xTaskResumeAll();

        taskYIELD();

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
    taskDISABLE_INTERRUPTS();

    xTaskCreate(vTask1, "Task 1", 2048, NULL, 1, &xTask1Handle);

    xTaskCreate(vTask2, "Task 2", 2048, NULL, 1, &xTask2Handle);

    vTaskSetApplicationTaskTag(xTask1Handle, (void *)uxTaskTag);

    taskENABLE_INTERRUPTS();

    vTaskStartScheduler();

    while (1)
    {
    }

    return 0;
}
