#include "rgb_led_modes.h"

static void set_pixel(led_strip_handle_t strip, uint8_t red, uint8_t green, uint8_t blue) {
    led_strip_set_pixel(strip, 0, red, green, blue);
    led_strip_refresh(strip);
}

void rgb_mode_red_blink(led_strip_handle_t strip) {
    static uint8_t step = 0;

    if ((step++ % 10) < 5) {
        set_pixel(strip, 255, 0, 0);
    } else {
        set_pixel(strip, 0, 0, 0);
    }
}

void rgb_mode_success(led_strip_handle_t strip) {
    set_pixel(strip, 0, 255, 0);
}

void rgb_mode_fail(led_strip_handle_t strip) {
    static uint8_t step = 0;

    if ((step++ % 6) < 3) {
        set_pixel(strip, 255, 0, 0);
    } else {
        set_pixel(strip, 0, 0, 0);
    }
}

void rgb_mode_commissioning_in_progress(led_strip_handle_t strip) {
    static uint8_t step = 0;

    switch (step++ % 3) {
        case 0:
            set_pixel(strip, 255, 0, 0);
            break;
        case 1:
            set_pixel(strip, 0, 255, 0);
            break;
        default:
            set_pixel(strip, 0, 0, 255);
            break;
    }
}

void rgb_mode_cycle_red_green(led_strip_handle_t strip) {
    static uint8_t step = 0;

    if ((step++ % 6) < 3) {
        set_pixel(strip, 255, 0, 0);
    } else {
        set_pixel(strip, 0, 255, 0);
    }
}
