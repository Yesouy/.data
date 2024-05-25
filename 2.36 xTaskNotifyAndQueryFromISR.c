#include "FreeRTOS.h"
#include "task.h"

void vTaskNotify(void *pvParameters)
{
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS(200);
    uint32_t ulValueToSend = 10;
    printf("Sending notification with value %lu\r\n", ulValueToSend);
    xTaskNotifyGiveIndexed(xTaskHandle, 0);
}