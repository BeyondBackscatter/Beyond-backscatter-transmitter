#include <stdio.h>
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"
 
static bool ON;
char buffer[4096];
 
void timer_callback(void *param)
{
    ON = !ON;
    
    gpio_set_level(GPIO_NUM_2, ON);
 
    // printf("%d \n", (int)ON);
//   ESP_LOGI("INFO", "status %d\n", (int)ON);
}
 
void print_val(void *arg)
{
    // printf();
}
 
void timer(void* arg){
 
    gpio_pad_select_gpio(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    const esp_timer_create_args_t my_timer_args = {
      .callback = &timer_callback,
      .name = "My Timer"};
    esp_timer_handle_t timer_handler;
    ESP_ERROR_CHECK(esp_timer_create(&my_timer_args, &timer_handler));
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, 250));
 
    while (1)
    {
        // esp_timer_dump(stdout);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
}
 
void app_main(void)
{
    xTaskCreate(&timer, "timer_task", 4096, NULL, 1, NULL);
}
