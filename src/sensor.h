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
 * @param _delay_in_us A pointer to the delay between measurement start and end (in microseconds).
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t sensor_init(struct bme280_dev* _device, uint32_t* _delay_in_us);

/**
 * Reads data from the BME280, processes the raw data, and stores the measurements
 * in the data structure.
 *
 * @param _device A pointer to the BME280 device driver structure.
 * @param _data A pointer to the data structure.
 * @param _delay_in_us The delay between measurement start and end (in microseconds).
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t sensor_read(struct bme280_dev* _device, struct measurements* _measurements, uint32_t _delay_in_us);

#endif
