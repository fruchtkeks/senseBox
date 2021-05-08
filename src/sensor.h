#ifndef SENSEBOX_SENSOR_H
#define SENSEBOX_SENSOR_H

// C
#include <stdint.h>

// External
#include "bme280.h"

// Internal
#include "common.h"

int32_t sensor_init(struct bme280_dev* _device);

int32_t sensor_read(struct bme280_dev* _device, struct data* _data);

#endif
