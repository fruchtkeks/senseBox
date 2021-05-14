#ifndef SENSEBOX_CONFIG_H
#define SENSEBOX_CONFIG_H

// C
#include <stddef.h>
#include <stdint.h>

// Internal
#include "common.h"

int32_t config_parseFromFile(const char* _fullpath, struct config* _config);

int32_t config_parse(char* _data, size_t _data_size, struct config* _config);

#endif
