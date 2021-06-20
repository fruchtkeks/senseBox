#include "sensor.h"

// C
#include <errno.h>
#include <stdio.h>
#include <string.h>

// Linux
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>

static int8_t user_i2c_read(uint8_t _register_address, uint8_t* _data, uint32_t _data_length, void* _intf_ptr)
{
	int8_t return_value = 0;

	int fd = -1;

	errno = 0;

	if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) {
		fprintf(stderr, "Unable to open device (%s)\n", strerror(errno));
		return 1;
	}

	struct i2c_rdwr_ioctl_data message_set[1];
	struct i2c_msg messages[2];

	messages[0].addr = (uint16_t)BME280_I2C_ADDR_PRIM;
	messages[0].flags = 0;
	messages[0].len = 1;
	messages[0].buf = &_register_address;

	messages[1].addr = (uint16_t)BME280_I2C_ADDR_PRIM;
	messages[1].flags = I2C_M_RD | I2C_M_NOSTART;
	messages[1].len = _data_length;
	messages[1].buf = _data;

	message_set[0].msgs = messages;
	message_set[0].nmsgs = 2;

	if (ioctl(fd, I2C_RDWR, &message_set) < 0) {
		fprintf(stderr, "Can't read from sensor (%s)\n", strerror(errno));
		return_value = 1;
	}

	close(fd);

	return return_value;
}

static int8_t user_i2c_write(uint8_t _register_address, const uint8_t* _data, uint32_t _data_length, void* _intf_ptr)
{
	int8_t return_value = 0;

	int fd = -1;

	errno = 0;

	if ((fd = open("/dev/i2c-1", O_RDWR)) < 0) {
		fprintf(stderr, "Unable to open device (%s)\n", strerror(errno));
		return 1;
	}

	struct i2c_rdwr_ioctl_data message_set[1];
	struct i2c_msg messages[1];

	uint8_t payload[1 + _data_length];

	payload[0] = _register_address;

	for (size_t position = 0; position < _data_length; ++position) {
		payload[position + 1] = _data[position];
	}

	messages[0].addr = (uint16_t)BME280_I2C_ADDR_PRIM;
	messages[0].flags = 0;
	messages[0].len = 1 + _data_length;
	messages[0].buf = payload;

	message_set[0].msgs = messages;
	message_set[0].nmsgs = 1;

	errno = 0;

	if (ioctl(fd, I2C_RDWR, &message_set) < 0) {
		fprintf(stderr, "Can't write to sensor (%s)\n", strerror(errno));
		return_value = 1;
	}

	close(fd);

	return return_value;
}

static void user_delay_us(uint32_t _period, void* _intf_ptr) { usleep(_period); }

// Tests

static int8_t sensor_dummy_read(uint8_t _register_address, uint8_t* _data, uint32_t _data_length, void* _intf_ptr)
{
	return 1;
}

static int8_t sensor_dummy_write(uint8_t _register_address, const uint8_t* _data, uint32_t _data_length,
								 void* _intf_ptr)
{
	return 1;
}

//

int32_t sensor_init(struct bme280_dev* _device)
{
	int8_t result = 0;

	_device->intf = BME280_I2C_INTF;

#if TESTS
	_device->read = sensor_dummy_read;
	_device->write = sensor_dummy_write;
#else
	_device->read = user_i2c_read;
	_device->write = user_i2c_write;
#endif

	_device->delay_us = user_delay_us;

	result = bme280_init(_device);

	if (result != 0) {
		fprintf(stderr, "Sensor init. failed (%s)\r\n", strerror(errno));
		return 1;
	}

	uint8_t sensor_select = BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_OSR_PRESS_SEL | BME280_FILTER_SEL;

	_device->settings.osr_t = BME280_OVERSAMPLING_2X;
	_device->settings.osr_h = BME280_OVERSAMPLING_1X;
	_device->settings.osr_p = BME280_OVERSAMPLING_16X;
	_device->settings.filter = BME280_FILTER_COEFF_16;

	result = bme280_set_sensor_settings(sensor_select, _device);

	if (result != 0) {
		fprintf(stderr, "Sensor setup failed (%s)\n", strerror(errno));
		return 1;
	}

	return 0;
}

int32_t sensor_read(struct bme280_dev* _device, struct measurements* _measurements)
{
	int8_t result = 0;

	uint32_t delay = bme280_cal_meas_delay(&_device->settings);

	struct bme280_data computed_data;

	_measurements->valid_ = false;
	_measurements->temperature_ = 0;
	_measurements->humidity_ = 0;
	_measurements->pressure_ = 0;

	result = bme280_set_sensor_mode(BME280_FORCED_MODE, _device);

	if (result != 0) {
		fprintf(stderr, "Setting measurement mode failed (%s)\r\n", strerror(errno));
		return 1;
	}

	_device->delay_us(delay, _device->intf_ptr);
	result = bme280_get_sensor_data(BME280_ALL, &computed_data, _device);

	if (result != 0) {
		fprintf(stderr, "Computing sensor measurements failed (%s)\r\n", strerror(errno));
		return 1;
	}

	_measurements->valid_ = true;
	_measurements->temperature_ = computed_data.temperature;
	_measurements->humidity_ = computed_data.humidity;
	_measurements->pressure_ = computed_data.pressure / 100.0;

	return 0;
}
