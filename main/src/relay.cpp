#include "relay.h"

#include "driver/gpio.h"
#include "esp_log.h"

#define RELAY_PIN GPIO_NUM_22
#define RELAY_DEFAULT_ON false
#define RELAY_ACTIVE_HIGH true

static const char *TAG = "RELAY";
static bool current_relay_state = RELAY_DEFAULT_ON;

static int relay_gpio_level_for_state(bool on) {
    if (RELAY_ACTIVE_HIGH) {
        return on ? 1 : 0;
    }
    return on ? 0 : 1;
}

esp_err_t relay_init(void) {
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1ULL << RELAY_PIN);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    esp_err_t gpio_ret = gpio_config(&io_conf);
    if (gpio_ret != ESP_OK) {
        ESP_LOGE(TAG, "GPIO configuration failed: %s", esp_err_to_name(gpio_ret));
        return gpio_ret;
    }

    gpio_ret = gpio_set_level(RELAY_PIN, relay_gpio_level_for_state(RELAY_DEFAULT_ON));
    if (gpio_ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set default relay state: %s", esp_err_to_name(gpio_ret));
        return gpio_ret;
    }

    current_relay_state = RELAY_DEFAULT_ON;
    ESP_LOGI(TAG, "GPIO initialized successfully. Default relay state: %d", current_relay_state);
    return ESP_OK;
}

esp_err_t relay_set(bool state) {
    esp_err_t gpio_ret = gpio_set_level(RELAY_PIN, relay_gpio_level_for_state(state));
    if (gpio_ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set relay state: %s", esp_err_to_name(gpio_ret));
        return gpio_ret;
    }

    current_relay_state = state;
    ESP_LOGI(TAG, "Relay state set to: %d", state);
    return ESP_OK;
}

bool relay_get(void) {
    return current_relay_state;
}
