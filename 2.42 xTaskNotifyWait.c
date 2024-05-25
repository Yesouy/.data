#include "FreeRTOS.h"
#include "task.h"

void vTaskNotifyWait(void *pvParameters)
{
    uint32_t ulNotificationValue;
    for (;;)
    {
        if (xTaskNotifyWait(0x00, ULONG_MAX, &ulNotificationValue, portMAX_DELAY) == pdPASS) {
            printf("Received Notification with value: %lu\r\n", ulNotificationValue);
        }
    }
}
