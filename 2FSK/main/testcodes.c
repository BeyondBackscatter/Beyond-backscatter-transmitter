#include <math.h>
#include "driver/ledc.h"
#include "esp_err.h"

#define MOTOR_PWM_CHANNEL_LEFT LEDC_CHANNEL_1
#define MOTOR_PWM_CHANNEL_RIGHT LEDC_CHANNEL_2
#define MOTOR_PWM_TIMER LEDC_TIMER_1
#define MOTOR_PWM_BIT_NUM LEDC_TIMER_10_BIT

#define RIGHT_PWM_PIN GPIO_NUM_19
#define LEFT_PWM_PIN GPIO_NUM_21

void motor_pwm_init(void)
{
    ledc_channel_config_t ledc_channel_left = {0}, ledc_channel_right = {0};
    ledc_channel_left.gpio_num = LEFT_PWM_PIN;
    ledc_channel_left.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_left.channel = MOTOR_PWM_CHANNEL_LEFT;
    ledc_channel_left.intr_type = LEDC_INTR_DISABLE;
    ledc_channel_left.timer_sel = MOTOR_PWM_TIMER;
    ledc_channel_left.duty = 0;
	
    ledc_channel_right.gpio_num = RIGHT_PWM_PIN;
    ledc_channel_right.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_channel_right.channel = MOTOR_PWM_CHANNEL_RIGHT;
    ledc_channel_right.intr_type = LEDC_INTR_DISABLE;
    ledc_channel_right.timer_sel = MOTOR_PWM_TIMER;
    ledc_channel_right.duty = 0;
	
    ledc_timer_config_t ledc_timer = {0};
    ledc_timer.speed_mode = LEDC_HIGH_SPEED_MODE;
    ledc_timer.bit_num = MOTOR_PWM_BIT_NUM;
    ledc_timer.timer_num = MOTOR_PWM_TIMER;
    ledc_timer.freq_hz = 25000;
	
	ESP_ERROR_CHECK( ledc_channel_config(&ledc_channel_left) );
	ESP_ERROR_CHECK( ledc_channel_config(&ledc_channel_right) );
	ESP_ERROR_CHECK( ledc_timer_config(&ledc_timer) );
}

void motor_pwm_set(float left_duty_fraction, float right_duty_fraction) {
	uint32_t max_duty = (1 << MOTOR_PWM_BIT_NUM) - 1;
	uint32_t left_duty = lroundf(left_duty_fraction * (float)max_duty);
	uint32_t right_duty = lroundf(right_duty_fraction * (float)max_duty);
	
	ESP_ERROR_CHECK( ledc_set_duty(LEDC_HIGH_SPEED_MODE, MOTOR_PWM_CHANNEL_LEFT, left_duty) );
	ESP_ERROR_CHECK( ledc_update_duty(LEDC_HIGH_SPEED_MODE, MOTOR_PWM_CHANNEL_LEFT) );

	ESP_ERROR_CHECK( ledc_set_duty(LEDC_HIGH_SPEED_MODE, MOTOR_PWM_CHANNEL_RIGHT, right_duty) );
	ESP_ERROR_CHECK( ledc_update_duty(LEDC_HIGH_SPEED_MODE, MOTOR_PWM_CHANNEL_RIGHT) );
}