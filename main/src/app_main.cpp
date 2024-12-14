#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"
#include <portmacro.h>
#include "driver/gpio.h"

#include "matter_interface.h"

#define RELAY_PIN GPIO_NUM_21

static const char *TAG = "***app_main***";

esp_err_t attribute_update_callback(const esp_matter::attribute::callback_type_t type,
                                       const uint16_t endpoint_id, const uint32_t cluster_id,
                                       const uint32_t attribute_id, esp_matter_attr_val_t *val,
                                       void *priv_data) {
    if (type == esp_matter::attribute::callback_type_t::PRE_UPDATE) {

        // Validate the attribute value
        if (val && val->type == ESP_MATTER_VAL_TYPE_BOOLEAN) {
            // Set the relay state based on the attribute value
            gpio_set_level(RELAY_PIN, val->val.b);
            ESP_LOGI(TAG, "Relay state set to: %d", val->val.b);
        } else {
            ESP_LOGE(TAG, "Invalid attribute value or type.");
            return ESP_ERR_INVALID_ARG;
        }

    } else if (type == esp_matter::attribute::callback_type_t::POST_UPDATE) {
        ESP_LOGI(TAG, "POST_UPDATE triggered.");
        // Additional actions can be implemented here
    }

    return ESP_OK;
}


extern "C" void app_main() {

    // Initialize NVS
    ESP_LOGI(TAG, "Initializing NVS...");
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "Erasing NVS partition...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }
    ESP_LOGI(TAG, "NVS initialized.");

    // Initialize GPIO
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

    // Initialize Matter
    ESP_LOGI(TAG, "Initializing Matter interface...");
    uint16_t ep_id;
    err = matter_init(&ep_id, attribute_update_callback);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Matter initialization failed: %s", esp_err_to_name(err));
        return;
    }
    ESP_LOGI(TAG, "Matter initialized.");

}