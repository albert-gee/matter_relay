#include "events.h"
#include "relay.h"

#include <esp_matter.h>
#include <esp_matter_attribute_utils.h>
#include <rgb_led.h>
#include <rgb_led_modes.h>
#include <platform/CHIPDeviceEvent.h>
#include <driver/gpio.h>

#include <esp_log.h>
#include <esp_err.h>
#include <inttypes.h>

static const char *TAG = "EVENTS";

void matter_event_callback(const ChipDeviceEvent *event, intptr_t arg) {
    switch (event->Type) {

        // Indicates that the commissioning window is now open.
        case chip::DeviceLayer::DeviceEventType::kCommissioningWindowOpened:
            ESP_LOGI(TAG, "Commissioning window opened");
            set_rgb_mode(rgb_mode_red_blink);
        	break;

        // Signals that a commissioning session has started.
        case chip::DeviceLayer::DeviceEventType::kCommissioningSessionStarted:
            ESP_LOGI(TAG, "Commissioning session started");
            // Set the RGB LED to a cycle colors mode
            set_rgb_mode(rgb_mode_commissioning_in_progress);
            break;

        // Signals that commissioning has completed via the general commissioning cluster command.
        case chip::DeviceLayer::DeviceEventType::kCommissioningComplete:
            ESP_LOGI(TAG, "Commissioning complete");
            set_rgb_mode(rgb_mode_success);
            break;

        // Indicates that the fail-safe timer expired before the CommissioningComplete command was invoked.
        case chip::DeviceLayer::DeviceEventType::kFailSafeTimerExpired:
            ESP_LOGI(TAG, "Commissioning failed, fail-safe timer expired");
            set_rgb_mode(rgb_mode_fail);
            break;

        // Indicates that the commissioning window is now closed.
        case chip::DeviceLayer::DeviceEventType::kCommissioningWindowClosed:
            ESP_LOGI(TAG, "Commissioning window closed");
            break;

        // Signals that a commissioning session has stopped.
        case chip::DeviceLayer::DeviceEventType::kCommissioningSessionStopped:
            ESP_LOGI(TAG, "Commissioning session stopped");
            break;

        case chip::DeviceLayer::DeviceEventType::kBLEDeinitialized:
            ESP_LOGI(TAG, "BLE deinitialized");
            set_rgb_mode(nullptr);
            break;

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

esp_err_t matter_attribute_update_callback(esp_matter::attribute::callback_type_t type, uint16_t endpoint_id, uint32_t cluster_id, uint32_t attribute_id,
                                           esp_matter_attr_val_t *val, void *priv_data) {
    if (type == esp_matter::attribute::callback_type_t::PRE_UPDATE) {
        if (val) {
            switch (val->type) {
                case ESP_MATTER_VAL_TYPE_BOOLEAN:
                    // Set the relay state based on the attribute value
                    relay_set(val->val.b);
                    ESP_LOGI(TAG, "Relay state set to: %d", val->val.b);
                    break;

                default:
                    ESP_LOGI(TAG, "Unknown attribute type: %d", val->type);
                    break;
            }
        }
    } else if (type == esp_matter::attribute::callback_type_t::POST_UPDATE) {
        ESP_LOGI(TAG, "POST_UPDATE triggered for endpoint %" PRIu32 ", cluster %" PRIu32 ", attribute %" PRIu32 ".",
                 (uint32_t)endpoint_id, (uint32_t)cluster_id, (uint32_t)attribute_id);
    }

    return ESP_OK;
}

esp_err_t identification_callback(esp_matter::identification::callback_type_t const type, uint16_t const endpoint_id,
                                  uint8_t const effect_id, uint8_t const effect_variant, void *priv_data) {
    ESP_LOGI(TAG, "Identification Callback Invoked: type=%d, endpoint_id=%u, effect_id=%u, effect_variant=%u",
             type, (unsigned int)endpoint_id, (unsigned int)effect_id, (unsigned int)effect_variant);
    return ESP_OK;
}
