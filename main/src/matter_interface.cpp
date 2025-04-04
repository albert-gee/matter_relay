#include "matter_interface.h"
#include "events.h"

#include <esp_log.h>
#include <esp_err.h>
#include <esp_matter.h>
#include <esp_matter_console.h>
#include <freertos/FreeRTOS.h>
#include <portmacro.h>

#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
#include <platform/ESP32/OpenthreadLauncher.h>
#endif

static const char *TAG = "***matter_interface***";

esp_err_t matter_init(uint16_t *endpoint_id) {
#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
    #define ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG()                                           \
    {                                                                                   \
    .radio_mode = RADIO_MODE_NATIVE,                                                \
    }

    #define ESP_OPENTHREAD_DEFAULT_HOST_CONFIG()                                            \
    {                                                                                   \
    .host_connection_mode = HOST_CONNECTION_MODE_NONE,                              \
    }

    #define ESP_OPENTHREAD_DEFAULT_PORT_CONFIG()                                            \
    {                                                                                   \
    .storage_partition_name = "nvs", .netif_queue_size = 10, .task_queue_size = 10, \
    }
#endif

#if CHIP_DEVICE_CONFIG_ENABLE_THREAD
    /* Set OpenThread platform config */
    esp_openthread_platform_config_t config = {
        .radio_config = ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_OPENTHREAD_DEFAULT_HOST_CONFIG(),
        .port_config = ESP_OPENTHREAD_DEFAULT_PORT_CONFIG(),
    };
    set_openthread_platform_config(&config);
#endif

    // Initialize Matter Node, where
    // - node_config is the configuration object for the nodeset_callback
    // - attribute_update_cb is the callback for handling attribute updates
    // - identification_callback is the callback for handling identification queries
    esp_matter::node::config_t node_config;
    esp_matter::node_t *matter_node = esp_matter::node::create(
        &node_config, matter_attribute_update_callback, identification_callback);
    if (matter_node == nullptr) {
        ESP_LOGE(TAG, "Failed to create Matter node.");
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "Matter node created");

    if (create_on_off_endpoint(matter_node, endpoint_id) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize on-off endpoint.");
        return ESP_FAIL;
    }

    esp_err_t matter_err = esp_matter::start(matter_event_callback);
    if (matter_err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start Matter, error: %d", matter_err);
        return matter_err;
    }
    ESP_LOGI(TAG, "Matter started");

    // The Matter Over-The-Air is a process that allows a Matter device in a Matter fabric to update its firmware.
    // OTA Requestor is any Matter device that is going to have its firmware updated.
    // https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/protocols/matter/overview/dfu.html
    // The esp-matter SDK supports using a pre-encrypted application image for OTA upgrades.
#if CONFIG_ENABLE_ENCRYPTED_OTA
    extern const char decryption_key_start[] asm("_binary_esp_image_encryption_key_pem_start");
    extern const char decryption_key_end[] asm("_binary_esp_image_encryption_key_pem_end");

    static const char *s_decryption_key = decryption_key_start;
    static const uint16_t s_decryption_key_len = decryption_key_end - decryption_key_start;

    esp_err_t err = esp_matter_ota_requestor_encrypted_init(s_decryption_key, s_decryption_key_len);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize encrypted OTA, err: %d", err);
    }
#endif // CONFIG_ENABLE_ENCRYPTED_OTA

    // Console shell is helpful when developing/debugging the application.
    // Set CONFIG_ENABLE_CHIP_SHELL=n in sdkconfig.defaults in production.
    // https://docs.espressif.com/projects/esp-matter/en/latest/esp32/optimizations.html
#if CONFIG_ENABLE_CHIP_SHELL
    esp_matter::console::diagnostics_register_commands();
    esp_matter::console::wifi_register_commands();
#if CONFIG_OPENTHREAD_CLI
    console::otcli_register_commands();
#endif
    esp_matter::console::init();
#endif

    return ESP_OK;
}

esp_err_t matter_update_value(const uint16_t endpoint_id, const bool new_value) {
    esp_matter_attr_val_t matter_new_val = esp_matter_bool(new_value);
    const esp_err_t ret = esp_matter::attribute::update(
        endpoint_id,
        chip::app::Clusters::OnOff::Id,
        chip::app::Clusters::OnOff::Attributes::OnOff::Id,
        &matter_new_val);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to update OnOff endpoint with new value");
        return ret;
    }

    ESP_LOGI(TAG, "OnOff endpoint updated with new value: %d", new_value);

    return ESP_OK;
}

esp_err_t create_on_off_endpoint(esp_matter::node_t *matter_node, uint16_t *endpoint_id) {
    esp_matter::endpoint::on_off_light::config_t on_off_light_config;
    esp_matter::endpoint_t *endpoint = esp_matter::endpoint::on_off_light::create(
        matter_node,
        &on_off_light_config,
        esp_matter::ENDPOINT_FLAG_NONE,
        nullptr
    );

    if (endpoint == nullptr) {
        ESP_LOGE(TAG, "Failed to create on/off endpoint.");
        return ESP_FAIL;
    }

    *endpoint_id = esp_matter::endpoint::get_id(endpoint);
    ESP_LOGI(TAG, "Relay created with endpoint_id %d", *endpoint_id);

    return ESP_OK;
}
