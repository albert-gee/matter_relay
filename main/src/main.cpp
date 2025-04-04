#include "esp_log.h"
#include "esp_err.h"
#include "nvs_flash.h"

#include "matter_interface.h"
#include "events.h"
#include "relay.h"

static const char *TAG = "***app_main***";

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
    init_relay();

    // Initialize Matter
    ESP_LOGI(TAG, "Initializing Matter interface...");
    uint16_t ep_id;
    err = matter_init(&ep_id);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Matter initialization failed: %s", esp_err_to_name(err));
        return;
    }
    ESP_LOGI(TAG, "Matter initialized.");

}