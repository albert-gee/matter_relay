#ifndef RELAY_H
#define RELAY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void init_relay(void);

void relay_set(bool state);

#ifdef __cplusplus
}
#endif
#endif //RELAY_H
