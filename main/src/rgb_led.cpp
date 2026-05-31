#include "rgb_led.h"
#include "rgb_led_modes.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "esp_err.h"
#include "esp_log.h"
#include "sdkconfig.h"

#if CONFIG_IDF_TARGET_ESP32
// GPIO6-GPIO11 are connected to SPI flash on ESP32. The relay board being
// flashed here is ESP32-D0WD, so GPIO8 watchdog-resets the chip when driven.
#define RGB_GPIO 21
#else
#define RGB_GPIO 8
#endif

static const char *TAG = "RGB_LED";

static TaskHandle_t rgb_task_handle = NULL;
static led_strip_handle_t strip = NULL;
static rgb_mode_fn current_mode = NULL;
static portMUX_TYPE current_mode_lock = portMUX_INITIALIZER_UNLOCKED;

static void turn_led_off(void) {
    led_strip_set_pixel(strip, 0, 0, 0, 0);
    led_strip_refresh(strip);
}

static rgb_mode_fn get_rgb_mode(void) {
    taskENTER_CRITICAL(&current_mode_lock);
    rgb_mode_fn mode = current_mode;
    taskEXIT_CRITICAL(&current_mode_lock);

    return mode;
}

static void rgb_task(void *pvParameter) {
    while (true) {
        rgb_mode_fn mode = get_rgb_mode();

        if (mode == NULL) {
            turn_led_off();
        } else {
            mode(strip);
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

esp_err_t rgb_led_init(void) {
    if (rgb_task_handle != NULL) {
        return ESP_OK;
    }

    if (strip == NULL) {
        led_strip_config_t strip_config = {
            .strip_gpio_num = RGB_GPIO,
            .max_leds = 1,
        };

        led_strip_rmt_config_t rmt_config = {
            .resolution_hz = 10 * 1000 * 1000,
        };

        esp_err_t err = led_strip_new_rmt_device(&strip_config, &rmt_config, &strip);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to create RGB LED strip: %s", esp_err_to_name(err));
            return err;
        }
    }

    BaseType_t created = xTaskCreate(rgb_task, "rgb_task", 2048, NULL, 5, &rgb_task_handle);
    if (created != pdPASS) {
        ESP_LOGE(TAG, "Failed to create RGB LED task");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "RGB LED initialized");
    return ESP_OK;
}

void set_rgb_mode(rgb_mode_fn mode) {
    taskENTER_CRITICAL(&current_mode_lock);
    current_mode = mode;
    taskEXIT_CRITICAL(&current_mode_lock);
}
