#ifndef SENSEBOX_SENSOR_H
#define SENSEBOX_SENSOR_H

// C
#include <stdint.h>

// External
#include "bme280.h"

// Internal
#include "common.h"

/**
 * Initializes the BME280 driver.
 *
 * @param _device A pointer to the BME280 device driver structure.
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t sensor_init(struct bme280_dev* _device);

/**
 * Reads data from the BME280, processes the raw data, and stores the measurements
 * in the data structure.
 *
 * @param _device A pointer to the BME280 device driver structure.
 * @param _data A pointer to the data structure.
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t sensor_read(struct bme280_dev* _device, struct measurements* _measurements);

#endif
