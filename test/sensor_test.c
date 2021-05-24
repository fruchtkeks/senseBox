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

	TEST_ASSERT(sensor_init(&device) == 1);
}

TEST(sensor, Read)
{
	struct bme280_dev device;
	struct measurements measurements;

	TEST_ASSERT(sensor_init(&device) == 1);
	TEST_ASSERT(sensor_read(&device, &measurements) == 1);
}
