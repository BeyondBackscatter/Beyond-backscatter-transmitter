#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/dac.h"
#include "freertos/semphr.h"
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>
#include <modulator.h>
#include <freertos/semphr.h>

TaskHandle_t clockTask;

bool ON = false;
TaskHandle_t freq1_task;
TaskHandle_t freq2_task;

// FSK modulation select - 2-FSK or 4-FSK
#define MODE_2FSK 2
#define MODE_4FSK 4
#define MODE MODE_4FSK
#define BUFFER_SIZE 10000
bool timer_started = false;
int mod_buffer[10000];
SemaphoreHandle_t bi_sema = NULL;

SemaphoreHandle_t task1Semaphore;
SemaphoreHandle_t task2Semaphore;

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

struct MODULATE *mod;
char buffer[50];
complex float baseband[CYCLES];
short word[CYCLES];

void frequency_gen1(void *pvParameters){

    while(1){
        int bitpair = 0; // digital baseband signal

        modulate(mod, baseband, bitpair); // modulation process

        for (int j = 0; j < CYCLES; j++) {
            // 50% modulation
            word[j] = (uint8_t) map_dac((short) ((crealf(baseband[j]) * 32767.0) / 2.0));
            dac_output_voltage(DAC_CHANNEL_1, word[j]);
            sprintf(buffer, "%hi\n", word[j]);
            printf("%s", buffer); // console prints
            // ESP_LOGI("debug", "%hi", word[j]);
        }


        // vTaskDelay(10 / portTICK_PERIOD_MS);
    }
            
}

void frequency_gen2(void *pvParameters){

    // struct MODULATE *mod;
    // char buffer[50];
    
    // if ((mod = mod_create(MODE, FS, RS, FIRST_TONE_FREQ, SHIFT_FREQ)) == NULL) {
    //     ESP_LOGE("debug", "Unable to create modulator");
    // }

    // complex float baseband[CYCLES];
    // short word[CYCLES];

    while(1){
                
        int bitpair = 1; // digital baseband signal

        modulate(mod, baseband, bitpair); // modulation process

        for (int j = 0; j < CYCLES; j++) {
            // 50% modulation
            word[j] = (uint8_t) map_dac((short) ((crealf(baseband[j]) * 32767.0) / 2.0));
            dac_output_voltage(DAC_CHANNEL_1, word[j]);
            sprintf(buffer, "%hi\n", word[j]);
            printf("%s", buffer); // console prints
            // ESP_LOGI("debug", "%hi", word[j]);
        }

        // vTaskDelay(10 / portTICK_PERIOD_MS);
    }
            
}

void timer_callback(void *param)
{
    ON = !ON;

    if (ON){
        if (mod->mode == MODE_2FSK) {
            mod->tone_1 = 1 & 0x1;
        }   
        else if (mod->mode == MODE_4FSK) {
            mod->tone_1 = 1 & 0x3;
        }

    /*
     * Grab one cycle of continuous phase
     * from the selected oscillator
     */
    for (int i = 0; i < mod->cycles; i++) {
        mod->phase *= mod->oscillator[mod->tone_1];
        baseband[i] = mod->phase;
        word[i] = (uint8_t) map_dac((short) ((crealf(baseband[i]) * 32767.0) / 2.0));
        dac_output_voltage(DAC_CHANNEL_1, word[i]);
        sprintf(buffer, "%hi\n", word[i]);
        printf("%s", buffer); // console prints
    }


        // vTaskSuspend(freq1_task);
        // vTaskResume(freq2_task);

    }
    else{

    if (mod->mode == MODE_2FSK) {
        mod->tone_1 = 0 & 0x1;
    } else if (mod->mode == MODE_4FSK) {
        mod->tone_1 = 0 & 0x3;
    }

    /*
     * Grab one cycle of continuous phase
     * from the selected oscillator
     */
    for (int i = 0; i < mod->cycles; i++) {
        mod->phase *= mod->oscillator[mod->tone_1];
        baseband[i] = mod->phase;
        word[i] = (uint8_t) map_dac((short) ((crealf(baseband[i]) * 32767.0) / 2.0));
        dac_output_voltage(DAC_CHANNEL_1, word[i]);
        sprintf(buffer, "%hi\n", word[i]);
        printf("%s", buffer); // console prints
    }

    /* Normalize phase */
    mod->phase /= cabsf(mod->phase);

        // vTaskSuspend(freq2_task);
        // vTaskResume(freq1_task);
    }
   
    gpio_set_level(GPIO_NUM_2, ON);

    // xTaskNotifyGive(task_handle_1);
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
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    
}

void app_main() {
   
    dac_output_enable(DAC_CHANNEL_1);
    if ((mod = mod_create(MODE, FS, RS, FIRST_TONE_FREQ, SHIFT_FREQ)) == NULL) {
        ESP_LOGE("debug", "Unable to create modulator");
    }
    // xTaskCreate(&frequency_gen2, "freq2", 8124, NULL, 1, &freq2_task); 
    // xTaskCreate(&frequency_gen1, "freq1", 8124, NULL, 1, &freq1_task);
    xTaskCreate(&timer, "task", 4096, NULL, 1, &clockTask); 

    // Initially take the semaphores to prevent immediate execution of tasks
    // xSemaphoreTake(task1Semaphore, portMAX_DELAY);
    // xSemaphoreTake(task2Semaphore, portMAX_DELAY);

}