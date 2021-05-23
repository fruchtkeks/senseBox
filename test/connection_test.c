// C
#include <string.h>

// External
#include "unity.h"
#include "unity_fixture.h"
#include <curl/curl.h>

// Internal
#include "connection.h"

TEST_GROUP(connection);

TEST_SETUP(connection) {}

TEST_TEAR_DOWN(connection) {}

TEST(connection, Init)
{
	CURL* curl = NULL;

	TEST_ASSERT(connection_init(&curl) == 0);
	TEST_ASSERT(curl != NULL);
}

TEST(connection, CleanUp)
{
	CURL* curl = NULL;

	TEST_ASSERT(connection_init(&curl) == 0);
	TEST_ASSERT(curl != NULL);
	connection_cleanup(&curl);
	TEST_ASSERT(curl == NULL);
}

TEST(connection, InitHeaders)
{
	struct curl_slist* headers = NULL;

	TEST_ASSERT(connection_initHeaders(&headers, "test") == 0);
	TEST_ASSERT(headers != NULL);
}

TEST(connection, CleanUpHeaders)
{
	struct curl_slist* headers = NULL;

	TEST_ASSERT(connection_initHeaders(&headers, "test") == 0);
	TEST_ASSERT(headers != NULL);
	connection_cleanupHeaders(&headers);
	TEST_ASSERT(headers == NULL);
}

TEST(connection, PrepareData)
{
	struct config config;
	struct measurements measurements;
	struct data data;

	strncpy(config.api_key_, "D43E6BF6547826753356E3CAE933033FAE02F940E0638305637BE0DE5ACE9026", API_KEY_SIZE);
	strncpy(config.box_id_, "350BB118888075D7D34908DE", BOX_ID_SIZE);
	strncpy(config.temperature_id_, "89A9477FBECC7D3E894C27B4", SENSOR_ID_SIZE);
	strncpy(config.humidity_id_, "5857D8ED75AF6E617B1BD921", SENSOR_ID_SIZE);
	strncpy(config.pressure_id_, "17BC7799401277B39B32BF39", SENSOR_ID_SIZE);

	measurements.valid_ = true;
	measurements.temperature_ = 12.34;
	measurements.humidity_ = 56.78;
	measurements.pressure_ = 91.23;

	TEST_ASSERT(connection_prepare(&config, &measurements, kSensorTemperature, &data) == 0);
	TEST_ASSERT(
		strcmp(data.url_, "https://ingress.opensensemap.org/boxes/350BB118888075D7D34908DE/89A9477FBECC7D3E894C27B4") ==
		0);

	TEST_ASSERT(connection_prepare(&config, &measurements, kSensorHumidity, &data) == 0);
	TEST_ASSERT(
		strcmp(data.url_, "https://ingress.opensensemap.org/boxes/350BB118888075D7D34908DE/5857D8ED75AF6E617B1BD921") ==
		0);

	TEST_ASSERT(connection_prepare(&config, &measurements, kSensorPressure, &data) == 0);
	TEST_ASSERT(
		strcmp(data.url_, "https://ingress.opensensemap.org/boxes/350BB118888075D7D34908DE/17BC7799401277B39B32BF39") ==
		0);

	TEST_ASSERT(connection_prepare(&config, &measurements, 99, &data) == 1);
}
