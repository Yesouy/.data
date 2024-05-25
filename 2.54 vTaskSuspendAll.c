#include "FreeRTOS.h"
#include "task.h"

void vTaskSuspendAll(void *pvParameters)
{
    vTaskSuspendAll();
    // Critical section 시작
    printf("Critical Section: All tasks suspended\r\n");
    // Critical section 종료
    xTaskResumeAll();
}
