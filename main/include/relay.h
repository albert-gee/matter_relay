#ifndef RELAY_H
#define RELAY_H

#include <stdbool.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t relay_init(void);

esp_err_t relay_set(bool state);

bool relay_get(void);

#ifdef __cplusplus
}
#endif
#endif //RELAY_H
