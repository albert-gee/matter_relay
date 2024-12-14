#include <esp_log.h>
#include <esp_matter_console.h>
#include <esp_matter.h>

#include "matter_interface.h"

static auto TAG = "***matter_interface***";

void matter_event_callback(const ChipDeviceEvent *event, intptr_t arg) {
    switch (event->Type) {
        // Signals a change in connectivity of the device's Wi-Fi station interface.
        case chip::DeviceLayer::DeviceEventType::kWiFiConnectivityChange:
            ESP_LOGI(TAG, "Wi-Fi connectivity change");
            break;

        // Signals a change in connectivity of the device's Thread interface.
        case chip::DeviceLayer::DeviceEventType::kThreadConnectivityChange:
            ESP_LOGI(TAG, "Thread connectivity change");
            break;

        // Signals a change in the device's ability to communicate via the internet.
        case chip::DeviceLayer::DeviceEventType::kInternetConnectivityChange:
            ESP_LOGI(TAG, "Internet connectivity change");
            break;

        // Signals a change in the device's ability to communicate with a chip-enabled service.
        case chip::DeviceLayer::DeviceEventType::kServiceConnectivityChange:
            ESP_LOGI(TAG, "Service connectivity change");
            break;

        // Signals a change to the device's service provisioning state.
        case chip::DeviceLayer::DeviceEventType::kServiceProvisioningChange:
            ESP_LOGI(TAG, "Service provisioning change");
            break;

        // Signals a change to the device's real-time clock synchronization state.
        case chip::DeviceLayer::DeviceEventType::kTimeSyncChange:
            ESP_LOGI(TAG, "Time synchronization change");
            break;

        // Signals that an external entity has established a new CHIPoBLE connection with the device.
        case chip::DeviceLayer::DeviceEventType::kCHIPoBLEConnectionEstablished:
            ESP_LOGI(TAG, "BLE connection established");
            break;

        // Signals that an external entity has closed an existing CHIPoBLE connection with the device.
        case chip::DeviceLayer::DeviceEventType::kCHIPoBLEConnectionClosed:
            ESP_LOGI(TAG, "BLE connection closed");
            break;

        // Request to close all BLE connections when concurrent connections are not supported.
        case chip::DeviceLayer::DeviceEventType::kCloseAllBleConnections:
            ESP_LOGI(TAG, "Close all BLE connections requested");
            break;

        // Indicates that the Wi-Fi device is available for connection.
        case chip::DeviceLayer::DeviceEventType::kWiFiDeviceAvailable:
            ESP_LOGI(TAG, "Wi-Fi device is available");
            break;

        // Indicates that the operational network has started.
        case chip::DeviceLayer::DeviceEventType::kOperationalNetworkStarted:
            ESP_LOGI(TAG, "Operational network started");
            break;

        // Signals a state change in the Thread stack.
        case chip::DeviceLayer::DeviceEventType::kThreadStateChange:
            ESP_LOGI(TAG, "Thread state change");
            break;

        // Indicates a change in the state of the Thread network interface.
        case chip::DeviceLayer::DeviceEventType::kThreadInterfaceStateChange:
            ESP_LOGI(TAG, "Thread interface state change");
            break;

        // Indicates a change in the CHIPoBLE advertising state.
        case chip::DeviceLayer::DeviceEventType::kCHIPoBLEAdvertisingChange:
            ESP_LOGI(TAG, "CHIPoBLE advertising state change");
            break;

        // Indicates that an IP address (IPv4 or IPv6) has changed for the interface.
        case chip::DeviceLayer::DeviceEventType::kInterfaceIpAddressChanged:
            ESP_LOGI(TAG, "Interface IP address changed");
            break;

        // Signals that commissioning has completed via the general commissioning cluster command.
        case chip::DeviceLayer::DeviceEventType::kCommissioningComplete:
            ESP_LOGI(TAG, "Commissioning complete");
            break;

        // Indicates that the fail-safe timer expired before the CommissioningComplete command was invoked.
        case chip::DeviceLayer::DeviceEventType::kFailSafeTimerExpired:
            ESP_LOGI(TAG, "Commissioning failed, fail-safe timer expired");
            break;

        // Indicates that the operational network is enabled.
        case chip::DeviceLayer::DeviceEventType::kOperationalNetworkEnabled:
            ESP_LOGI(TAG, "Operational network enabled");
            break;

        // Signals that DNS-SD has been initialized and is ready to operate.
        case chip::DeviceLayer::DeviceEventType::kDnssdInitialized:
            ESP_LOGI(TAG, "DNS-SD initialized");
            break;

        // Indicates that the DNS-SD backend was restarted and services must be published again.
        case chip::DeviceLayer::DeviceEventType::kDnssdRestartNeeded:
            ESP_LOGI(TAG, "DNS-SD restart needed");
            break;

        // Indicates that bindings were updated via cluster.
        case chip::DeviceLayer::DeviceEventType::kBindingsChangedViaCluster:
            ESP_LOGI(TAG, "Bindings updated via cluster");
            break;

        // Indicates a change in the OTA engine state.
        case chip::DeviceLayer::DeviceEventType::kOtaStateChanged:
            ESP_LOGI(TAG, "OTA state changed");
            break;

        // Indicates that server initialization has completed, and the node is ready for connections.
        case chip::DeviceLayer::DeviceEventType::kServerReady:
            ESP_LOGI(TAG, "Server is ready");
            break;

        // Signals that BLE has been deinitialized.
        case chip::DeviceLayer::DeviceEventType::kBLEDeinitialized:
            ESP_LOGI(TAG, "BLE deinitialized");
            break;

        // Signals that a commissioning session has started.
        case chip::DeviceLayer::DeviceEventType::kCommissioningSessionStarted:
            ESP_LOGI(TAG, "Commissioning session started");
            break;

        // Signals that a commissioning session has stopped.
        case chip::DeviceLayer::DeviceEventType::kCommissioningSessionStopped:
            ESP_LOGI(TAG, "Commissioning session stopped");
            break;

        // Indicates that the commissioning window is now open.
        case chip::DeviceLayer::DeviceEventType::kCommissioningWindowOpened:
            ESP_LOGI(TAG, "Commissioning window opened");
            break;

        // Indicates that the commissioning window is now closed.
        case chip::DeviceLayer::DeviceEventType::kCommissioningWindowClosed:
            ESP_LOGI(TAG, "Commissioning window closed");
            break;

        // Indicates that a fabric is about to be removed.
        case chip::DeviceLayer::DeviceEventType::kFabricWillBeRemoved:
            ESP_LOGI(TAG, "Fabric will be removed");
            break;

        // Indicates that a fabric has been removed.
        case chip::DeviceLayer::DeviceEventType::kFabricRemoved:
            ESP_LOGI(TAG, "Fabric removed successfully");
            break;

        // Indicates that a fabric in the Fabric Table has been committed to storage.
        case chip::DeviceLayer::DeviceEventType::kFabricCommitted:
            ESP_LOGI(TAG, "Fabric committed to storage");
            break;

        // Signals that operational credentials have been updated.
        case chip::DeviceLayer::DeviceEventType::kFabricUpdated:
            ESP_LOGI(TAG, "Fabric updated");
            break;

        default:
            ESP_LOGI(TAG, "Unhandled Matter event type: %d", event->Type);
            break;
    }
}

esp_err_t identification_callback(esp_matter::identification::callback_type_t const type, uint16_t const endpoint_id,
                                  uint8_t const effect_id, uint8_t const effect_variant, void *priv_data) {
    ESP_LOGI(TAG, "Identification Callback Invoked: type=%d, endpoint_id=%u, effect_id=%u, effect_variant=%u",
             type, (unsigned int)endpoint_id, (unsigned int)effect_id, (unsigned int)effect_variant);
    return ESP_OK;
}

esp_err_t matter_init(uint16_t *endpoint_id, esp_matter::attribute::callback_t attribute_update_cb) {

    // Initialize Matter Node, where
    // - node_config is the configuration object for the nodeset_callback
    // - attribute_update_cb is the callback for handling attribute updates
    // - identification_callback is the callback for handling identification queries
    esp_matter::node::config_t node_config;
    esp_matter::node_t *matter_node = esp_matter::node::create(
        &node_config, attribute_update_cb, identification_callback);
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
