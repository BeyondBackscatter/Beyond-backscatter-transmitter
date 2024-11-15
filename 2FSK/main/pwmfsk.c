

#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "packet_gen.h"
#include "esp_log.h"
#include <freertos/semphr.h>
#include "string_nvs.h"
#include "convolutional_encoder.h"
#include "reedSolomonEncoder.h"

#define TX_DURATION 50 // send a packet every 200ms (when changing baud-rate, ensure that the TX delay is larger than the transmission time)
#define RECEIVER 1352 // define the receiver board either 2500 or 1352

#define ITEM_SIZE sizeof(int)

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (4) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_3_BIT // Set duty resolution to 3 bits
#define LEDC_DUTY               (3) // Set duty to 50%. ((2 ** 3) - 1) * 50% = 3
#define LEDC_FREQUENCY_1        (read_message().freqlow) // Frequency in Hertz. Set frequency at 2 MHz
#define LEDC_FREQUENCY_2        (read_message().freqhigh) // Frequency in Hertz. Set frequency at 2.182 MHz
#define MAX_BUFFER_LENGTH       (PAYLOADSIZE+6)
#define TXLEN                   (LONG_RANGE_MODE==1)?(PAYLOADSIZE+6)*32:(PAYLOADSIZE+10)/4+1


TaskHandle_t task_handle_1;
QueueHandle_t queue;
esp_timer_handle_t timer_handler;

bool txbit;
bool recvd; 
int tx_buffer[TXLEN] = { 0 };
int tx_counter = 0;

void pwm_set_frequency(uint32_t frequency) {
    
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = frequency,  // Set output frequency
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));
}

void freq1()
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    pwm_set_frequency(LEDC_FREQUENCY_1);
}

void freq2()
{
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY));
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
    pwm_set_frequency(LEDC_FREQUENCY_2);
}

void timer_callback(void *param)
{
    if (tx_counter < TXLEN)
    {
        xQueueReceive(queue, &recvd, pdMS_TO_TICKS(10));
        if (recvd == 1){
            freq2();
        }
        else{
            freq1();
        }
        // printf("%d",recvd);
        // gpio_set_level(GPIO_NUM_2, recvd);
        tx_counter++;
    }
    else
    {
        tx_counter = 0;
        xQueueReset(queue);
        esp_timer_stop(timer_handler);
        esp_timer_delete(timer_handler);
        // printf("tx complete\n");
        // gpio_set_level(GPIO_NUM_2, 0);
    }
}

void timer(void* param){

    // gpio_pad_select_gpio(GPIO_NUM_2);
    // gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    const esp_timer_create_args_t my_timer_args = {
        .callback = &timer_callback,
        .arg = NULL,
        .name = "tx timer"};
    
    ESP_ERROR_CHECK(esp_timer_create(&my_timer_args, &timer_handler));
    ESP_ERROR_CHECK(esp_timer_start_periodic(timer_handler, read_message().baud));

    while (1)
    {
        // esp_timer_dump(stdout);
        // vTaskDelay(1/portTICK_PERIOD_MS);
    }
}

void uint32_to_binary(uint32_t num) {

    // Start from the leftmost bit (31st bit)
    uint32_t mask = 1 << 31;
    
    // Iterate through each bit
    for (int i = 0; i < 32; i++) {
        // Check if the bit is set or not
        txbit = num & mask;
        xQueueSend(queue, &txbit, 0);
        // Shift the mask to the right for the next bit
        mask >>= 1;
    }
}
void send(uint8_t *tx_payload_buffer)
{
    uint8_t message[MAX_BUFFER_LENGTH*4] = {0};  // include 10 header bytes
    uint32_t buffer[MAX_BUFFER_LENGTH] = {0};  // initialize the buffer
    uint16_t seq = 0;
    uint8_t *header_tmplate = packet_hdr_template(RECEIVER);
    xQueueReset(queue);
    if (LONG_RANGE_MODE==0)
    {
        add_header(&message[0], seq, header_tmplate);
        /* add payload to packet */
        memcpy(&message[HEADER_LEN], tx_payload_buffer, PAYLOADSIZE);

        for (uint8_t i=0; i < buffer_size(PAYLOADSIZE, HEADER_LEN); i++) {
            buffer[i] = ((uint32_t) message[4*i+3]) | (((uint32_t) message[4*i+2]) << 8) | (((uint32_t) message[4*i+1]) << 16) | (((uint32_t)message[4*i]) << 24);
            // printf("%x \n",buffer[i]);
            uint32_to_binary(buffer[i]); 
        }
    }
    else if (LONG_RANGE_MODE==1)
    {
        fill_buffer_in_long_range_mode_1(buffer,tx_payload_buffer,14,seq);
        for(int i=0;i<(20);i++)
    {    
            uint32_to_binary(buffer[i]);
        }
    }

    //transmit
    tx_counter = 0;
    xTaskCreate(&timer, "task", 8192,(void *)queue, 1, &task_handle_1); //transmitter
    vTaskDelay(TX_DURATION/portTICK_PERIOD_MS);

    vTaskDelete(task_handle_1);
}

void packet_task(void* arg){
    // This initialization is just for debugging purposes

    uint8_t tx_payload_buffer[PAYLOADSIZE]={0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd};

    while (true) {
        /* generate new data */
        // generate_pseudo_random_payload(tx_payload_buffer, PAYLOADSIZE);
            // for(int i=0;i<14;i++)
            //     printf("%2x",tx_payload_buffer[i]);
            // printf("\n");
        // uint8_t tx_payload_buffer[PAYLOADSIZE]={0};
        /* add header (10 byte) to packet */
        if (REED_SOLOMON ==0)
        {
            send(tx_payload_buffer);
        }
        else if(REED_SOLOMON==1)
        {
        uint8_t encoded_tx_payload_buffer[2*PAYLOADSIZE]={0};
        encodeReedSolomon(tx_payload_buffer,encoded_tx_payload_buffer);       
        uint8_t packet_to_be_sent[PAYLOADSIZE]={0};
        for (int i=0;i<2*PAYLOADSIZE;i++)
        {  
            for (int j=0;j<14;j++)
                packet_to_be_sent[j]= encoded_tx_payload_buffer[i];
            send(packet_to_be_sent);

        }
        }
    }
}

void app_main(void)
{

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    queue = xQueueCreate(TXLEN, ITEM_SIZE);
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    // xTaskCreate(&start_tuning_http_server, "start_tuning_http_server", 4096, NULL, 1, NULL);
    xTaskCreate(&packet_task, "packet", 8192, (void *)queue, 1, NULL);
}
