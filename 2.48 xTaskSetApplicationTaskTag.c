#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t xTaskTagHandle = NULL;

void vTaskTag(void *pvParameters);

int main(void) {
    xTaskCreate(vTaskTag, "Task 1", 1000, NULL, 1, &xTaskTagHandle);


    vTaskSetApplicationTaskTag(xTaskTagHandle, (void *)1);

    vTaskStartScheduler();
    for(;;);
}

void vTaskTag(void *pvParameters) {
    for (;;) {

        int tag = (int)pvTaskGetApplicationTaskTag(NULL);

    }
}
