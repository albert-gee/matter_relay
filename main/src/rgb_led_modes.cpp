#include "rgb_led_modes.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void rgb_mode_red_blink(led_strip_handle_t strip) {
    while (1) {
        led_strip_set_pixel(strip, 0, 255, 0, 0);  // Red
        led_strip_refresh(strip);
        vTaskDelay(500 / portTICK_PERIOD_MS);

        led_strip_set_pixel(strip, 0, 0, 0, 0);  // Off
        led_strip_refresh(strip);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void rgb_mode_success(led_strip_handle_t strip) {
    led_strip_set_pixel(strip, 0, 0, 255, 0);  // Green
    led_strip_refresh(strip);
}

void rgb_mode_fail(led_strip_handle_t strip) {
    while (1) {
        led_strip_set_pixel(strip, 0, 255, 0, 0);  // Red
        led_strip_refresh(strip);
        vTaskDelay(300 / portTICK_PERIOD_MS);

        led_strip_set_pixel(strip, 0, 0, 0, 0);  // Off
        led_strip_refresh(strip);
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}

void rgb_mode_commissioning_in_progress(led_strip_handle_t strip) {
    while (1) {
        led_strip_set_pixel(strip, 0, 255, 0, 0);  // Red
        led_strip_refresh(strip);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        led_strip_set_pixel(strip, 0, 0, 255, 0);  // Green
        led_strip_refresh(strip);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        led_strip_set_pixel(strip, 0, 0, 0, 255);  // Blue
        led_strip_refresh(strip);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void rgb_mode_cycle_red_green(led_strip_handle_t strip) {
    while (1) {
        led_strip_set_pixel(strip, 0, 255, 0, 0);  // Red
        led_strip_refresh(strip);
        vTaskDelay(300 / portTICK_PERIOD_MS);

        led_strip_set_pixel(strip, 0, 0, 255, 0);  // Green
        led_strip_refresh(strip);
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}
