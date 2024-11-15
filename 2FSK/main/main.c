#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "modulator.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/dac.h"
#include "freertos/semphr.h"

// FSK modulation select - 2-FSK or 4-FSK
#define MODE_2FSK 2
#define MODE_4FSK 4
#define MODE MODE_2FSK
#define BUFFER_SIZE 10000
static bool ON = false;
bool timer_started = false;
int mod_buffer[10000];
TaskHandle_t task_handle_1;
SemaphoreHandle_t bi_sema = NULL;

// Protocol select
#define LORA 1
#define BLE 2
#define PROT_MOD BLE // protocol mode

#if PROT_MOD == 1                            // LORA
    // printf("Selected protocol -> LORA\n");
    #define FIRST_TONE_FREQ 868000000        // ISM band -> 169, 433, 868 MHz (in Europe) and 915 MHz.
    #define SHIFT_FREQ 125000                // del_f -> 125 kHz, 250 kHz and 500 kHz
    #define FS 500000                        // sampling frequency - 5 MHz
    #define RS 1000                          // Symbol rate -> 1k symbols
#elif PROT_MOD == 2                          // BLE
    #define FIRST_TONE_FREQ 2400000000       // ISM band -> 2.4 GHzz
    #define SHIFT_FREQ 115000                // minimum def_f -> 115 kHz
    #define FS 1000000                       // sampling frequency - 1 MHz
    #define RS 2000                          // Symbol rate -> 2k symbols
#else
    // printf("Selected protocol -> Miscellanous\n");
    #define FIRST_TONE_FREQ 2400000000
    #define SHIFT_FREQ 200
    #define FS 8000
    #define RS 100
#endif

#define CYCLES (FS / RS)

int map_dac(short num){
    short old_max = 16500;
    short old_min = -16500;
    short new_max = 255;
    short new_min = 0;
    
    return ((num - old_min) * (new_max - new_min) / (old_max - old_min)) + new_min;
}

typedef struct {
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

void initCircularBuffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int isCircularBufferEmpty(CircularBuffer *cb) {
    return (cb->count == 0);
}

int isCircularBufferFull(CircularBuffer *cb) {
    return (cb->count == BUFFER_SIZE);
}

void enqueue(CircularBuffer *cb, int data) {
    if (isCircularBufferFull(cb)) {
        printf("Circular buffer is full. Unable to enqueue.\n");
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count++;
}

int dequeue(CircularBuffer *cb) {
    if (isCircularBufferEmpty(cb)) {
        printf("Circular buffer is empty. Unable to dequeue.\n");
        return -1;
    }
    int data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count--;
    return data;
}

CircularBuffer cb;

void mod_task(void *pvParameters){
    
    // CircularBuffer *cb = (CircularBuffer *)pvParameters;
    struct MODULATE *mod;
    char buffer[50];
    
    if ((mod = mod_create(MODE, FS, RS, FIRST_TONE_FREQ, SHIFT_FREQ)) == NULL) {
        ESP_LOGE("debug", "Unable to create modulator");
    }

    complex float baseband[CYCLES];
    short word[CYCLES];

    while(1){
                
        // ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // for (int i = 0; i < 512; i++) {
            int bitpair = (dequeue(&cb) % MODE); // digital baseband signal

            modulate(mod, baseband, bitpair); // modulation process
    
            // printf("%hi\n",(short)crealf(baseband[i]));
            // printf("%f\n", creal(baseband[i] * 32767.0) / 2.0);

            for (int j = 0; j < CYCLES; j++) {
                // 50% modulation
                word[j] = (uint8_t) map_dac((short) ((crealf(baseband[j]) * 32767.0) / 2.0));
                dac_output_voltage(DAC_CHANNEL_1, word[j]);
                sprintf(buffer, "%hi\n", word[j]);
                printf("%s", buffer); // console prints
                // ESP_LOGI("debug", "%hi", word[j]);
            }
        }
               
    // }      
}



void timer_callback(void *param)
{
    ON = !ON;
    enqueue(&cb, (int)ON);
    gpio_set_level(GPIO_NUM_2, ON);
    // xTaskNotifyGive(task_handle_1);
}

void print_val(void *arg)
{
    while (1)
    {
        printf("%d \n", (int)ON);
    }
    
}

void timer(void *pvParameters){

    // CircularBuffer *cb = (CircularBuffer *)pvParameters;

    gpio_pad_select_gpio(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    const esp_timer_create_args_t my_timer_args = {
      .callback = &timer_callback,
      .name = "My Timer"};
    esp_timer_handle_t timer_handler;
    ESP_ERROR_CHECK(esp_timer_create(&my_timer_args, &timer_handler));
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, 1000));

    while (1)
    {
        // esp_timer_dump(stdout);
        // vTaskDelay(pdMS_TO_TICKS(2000));
    }
    
}

void app_main(){
    dac_output_enable(DAC_CHANNEL_1);
    // xTaskCreate(&timer, "task", 4096, NULL, 1, NULL);
    // xTaskCreate(&mod_task, "mod_task", 8124, NULL, 1, &task_handle_1);
    xTaskCreatePinnedToCore(&mod_task, "mod_task", 8124, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(&timer, "task", 4096, NULL, 1, NULL, 1);
}
