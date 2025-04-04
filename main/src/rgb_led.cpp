#include "rgb_led.h"
#include "rgb_led_modes.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "esp_log.h"

#define RGB_GPIO 8

static TaskHandle_t rgb_task_handle = NULL;
static led_strip_handle_t strip = NULL;
static rgb_mode_fn current_mode = NULL;

static void rgb_task(void *pvParameter) {
    if (strip == NULL) {
        led_strip_config_t strip_config = {
            .strip_gpio_num = RGB_GPIO,
            .max_leds = 1,
        };

        led_strip_rmt_config_t rmt_config = {
            .resolution_hz = 10 * 1000 * 1000,
        };

        ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &strip));
    }

    if (current_mode) {
        current_mode(strip);
    }

    vTaskDelete(NULL);
}

void set_rgb_mode(rgb_mode_fn mode) {
    if (current_mode != mode) {
      vTaskDelay(3000 / portTICK_PERIOD_MS);

        // Avoid deleting a task that already self-deleted
        if (rgb_task_handle != NULL && eTaskGetState(rgb_task_handle) != eDeleted) {
            vTaskDelete(rgb_task_handle);
        }

        rgb_task_handle = NULL;
        current_mode = mode;

        if (current_mode == NULL) {
            // Turn off LED if no mode
            if (strip != NULL) {
                led_strip_set_pixel(strip, 0, 0, 0, 0);
                led_strip_refresh(strip);
            }
            return;
        }

        xTaskCreate(rgb_task, "rgb_task", 2048, NULL, 5, &rgb_task_handle);
    }
}
