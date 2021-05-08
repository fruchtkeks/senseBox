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

int main()
{
	struct bme280_dev device;

	struct config config;
	struct data data;

	CURL* curl;

	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Unable to register signal handler\r\n");
		return 1;
	}

	// Load and parse configuration
	config_load(&config);

	if (!config.valid_) {
		fprintf(stderr, "Unable to load / parse config\r\n");
		return 1;
	}

	// Setup network
	connection_init(&curl);

	// Check for sensor
	sensor_init(&device);

	printf("ID: 0x%X\r\n", device.chip_id);

	while (!terminate) {
		// Read and process data from sensor
		sensor_read(&device, &data);

		// Print data
		printf("Temp.: %0.2f °C - Hum.: %0.2f - Pressure: %0.2f hPa\r\n", data.temperature_, data.humidity_,
			   data.pressure_);

		// Send sensor data to server
		connection_send(&curl, &config, &data);

		// Sleep (60s)
		usleep(60000000);
	}

	connection_cleanup(&curl);

	return 0;
}
