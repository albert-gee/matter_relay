#include "relay.h"

#include "driver/gpio.h"
#include "esp_log.h"

#define RELAY_PIN GPIO_NUM_22

static const char *TAG = "RELAY";

void init_relay() {
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << RELAY_PIN);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    esp_err_t gpio_ret = gpio_config(&io_conf);
    if (gpio_ret != ESP_OK) {
        ESP_LOGE(TAG, "GPIO configuration failed: %s", esp_err_to_name(gpio_ret));
    } else {
        ESP_LOGI(TAG, "GPIO initialized successfully.");
    }
}

void relay_set(bool state) {
    esp_err_t gpio_ret = gpio_set_level(RELAY_PIN, state);
    if (gpio_ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set relay state: %s", esp_err_to_name(gpio_ret));
    } else {
        ESP_LOGI(TAG, "Relay state set to: %d", state);
    }
}