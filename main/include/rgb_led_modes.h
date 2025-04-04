#ifndef RGB_LED_MODES_H
#define RGB_LED_MODES_H

#include "led_strip.h"

#ifdef __cplusplus
extern "C" {
#endif

// Function for a red blink to indicate commissioning is in progress
void rgb_mode_red_blink(led_strip_handle_t strip);

// Function to show a solid green color for commissioning success
void rgb_mode_success(led_strip_handle_t strip);

// Function to flash red to indicate failure (e.g., fail-safe timer expired)
void rgb_mode_fail(led_strip_handle_t strip);

// Function to blink yellow to indicate commissioning in progress
void rgb_mode_commissioning_in_progress(led_strip_handle_t strip);

// Function to cycle between red and green to indicate device setup
void rgb_mode_cycle_red_green(led_strip_handle_t strip);

#ifdef __cplusplus
}
#endif

#endif // RGB_LED_MODES_H
