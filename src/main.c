// C
#include <stdbool.h>

// Linux
#include <signal.h>
#include <unistd.h>

// Internal
#include "config.h"
#include "connection.h"
#include "sensor.h"

bool terminate = false;

void signal_handler(int _signal)
{
	if (_signal == SIGINT) {
		terminate = true;
	}
}

int main(int argc, char* argv[])
{
	struct bme280_dev device;

	struct config config;
	struct measurements measurements;
	struct data data;

	CURL* curl = NULL;
	struct curl_slist* headers = NULL;

	if (argc != 2) {
		fprintf(stderr, "Missing path to config file\r\n");
		return 1;
	}

	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Unable to register signal handler\r\n");
		return 1;
	}

	// Load and parse configuration
	config_parseFromFile(argv[1], &config);

	if (!config.valid_) {
		fprintf(stderr, "Unable to load / parse config\r\n");
		return 1;
	}

	// Setup network
	if (connection_init(&curl) != 0) {
		fprintf(stderr, "Can't initialize cURL handle\r\n");
		return 1;
	}

	// Init cURL headers
	if (connection_initHeaders(&headers, config.api_key_) != 0) {
		fprintf(stderr, "Can't initialize the cURL header structure\r\n");
		return 1;
	}

	// Check for sensor
	sensor_init(&device);

	printf("ID: 0x%X\r\n", device.chip_id);

	while (!terminate) {
		// Read and process data from sensor
		sensor_read(&device, &measurements);

		// Print data
		printf("Temp.: %0.2f °C - Hum.: %0.2f - Pressure: %0.2f hPa\r\n", measurements.temperature_,
			   measurements.humidity_, measurements.pressure_);

		// Send measurements to openSenseMap
#if SEND_DATA
		for (size_t sensor = 0; sensor < kSensorSize; ++sensor) {
			if (connection_prepare(&config, &measurements, sensor, &data) != 0) {
				fprintf(stderr, "Preparing of data failed\r\n");
				continue;
			}

			if (connection_send(&curl, (const struct curl_slist**)&headers, &data) != 0) {
				fprintf(stderr, "Sending of data failed\r\n");
			}
		}
#endif

#if SHORT_SLEEP
		// Sleep (5s)
		usleep(5000000);
#else
		// Sleep (60s)
		usleep(60000000);
#endif
	}

	// Clean up cURL headers and cURL object
	connection_cleanupHeaders(&headers);
	connection_cleanup(&curl);

	return 0;
}
