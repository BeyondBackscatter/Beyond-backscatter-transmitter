#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

#define QUEUE_LENGTH 192
#define ITEM_SIZE sizeof(int)

QueueHandle_t queue;
TaskHandle_t task_handle_1;
int counter = 0; 

void receiver_task(void *pvParameters) {
    int received;

    while (1) {
        // Receive the integer from the queue
        xQueueReceive(queue, &received, portMAX_DELAY);

        printf("Received: %d\n", received);
    }
}

void sender_task(void *pvParameters) {

    while (1) {
        // Send the integer to the queue
        xQueueSend(queue, &counter, portMAX_DELAY);
        printf("Sent: %d\n", counter);
        counter++;
        if (counter >= QUEUE_LENGTH){
            counter = 0;
            xTaskCreate(receiver_task, "Receiver Task", 2048, (void *)queue, 1, NULL);

            vTaskDelete(task_handle_1);
        }

        // Delay for some time before sending the next integer
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}



void app_main() {
    queue = xQueueCreate(QUEUE_LENGTH, ITEM_SIZE);

    if (queue != NULL) {
        xTaskCreate(sender_task, "Sender Task", 2048, (void *)queue, 1, &task_handle_1);
    }
}
