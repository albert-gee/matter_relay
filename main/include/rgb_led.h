#ifndef RGB_LED_H
#define RGB_LED_H

#include "led_strip.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*rgb_mode_fn)(led_strip_handle_t strip);

void set_rgb_mode(rgb_mode_fn mode);

#ifdef __cplusplus
}
#endif

#endif // RGB_LED_H
