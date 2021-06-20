// External
#include "unity.h"
#include "unity_fixture.h"

// Internal
#include "sensor.h"

TEST_GROUP(sensor);

TEST_SETUP(sensor) {}

TEST_TEAR_DOWN(sensor) {}

TEST(sensor, Init)
{
	struct bme280_dev device;
	uint32_t delay_in_us = 0;

	TEST_ASSERT(sensor_init(&device, &delay_in_us) == 1);
}

TEST(sensor, Read)
{
	struct bme280_dev device;
	uint32_t delay_in_us = 0;
	struct measurements measurements;

	TEST_ASSERT(sensor_init(&device, &delay_in_us) == 1);
	TEST_ASSERT(sensor_read(&device, &measurements, delay_in_us) == 1);
}
