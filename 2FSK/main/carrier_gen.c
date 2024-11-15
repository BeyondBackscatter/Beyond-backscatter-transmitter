#include "esp_system.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "driver/periph_ctrl.h"
#include "soc/rmt_reg.h"

#define TAG "RF Carrier"

// RF frequency in Hz
#define RF_FREQUENCY 868000000

// RF carrier wave duty cycle (e.g., 50%)
#define CARRIER_DUTY_CYCLE 50

void app_main() {
    // Initialize RF driver
    esp_err_t err = esp_rf_init();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize RF driver");
        return;
    }

    // Set RF frequency
    err = esp_rf_set_frequency(RF_FREQUENCY);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set RF frequency");
        return;
    }

    // Enable carrier wave
    err = esp_rf_enable_carrier(CARRIER_DUTY_CYCLE);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to enable carrier wave");
        return;
    }

    // Keep the program running indefinitely
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
