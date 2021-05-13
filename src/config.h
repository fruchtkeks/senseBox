#ifndef SENSEBOX_CONFIG_H
#define SENSEBOX_CONFIG_H

// C
#include <stdint.h>

// Internal
#include "common.h"

int32_t config_load(const char* _path, struct config* _config);

#endif
