#include "config.h"

// C
#include <errno.h>
#include <stdio.h>
#include <string.h>

int32_t config_load(struct config* _config)
{
	FILE* file;
	char* line = NULL;
	size_t length = 0;
	ssize_t read;

	_config->valid_ = true;
	memset(_config->api_key_, 0, API_KEY_SIZE);
	memset(_config->box_id_, 0, BOX_ID_SIZE);
	memset(_config->temperature_id_, 0, SENSOR_ID_SIZE);
	memset(_config->humidity_id_, 0, SENSOR_ID_SIZE);
	memset(_config->pressure_id_, 0, SENSOR_ID_SIZE);

	errno = 0;

	file = fopen("box.config", "r");

	if (!file) {
		fprintf(stderr, "Unable to open config file (%s)\n", strerror(errno));
		return 1;
	}

	char* key;
	char* separator;
	char* value;

	while ((read = getline(&line, &length, file)) != -1) {
		key = line;
		separator = strchr(line, '=');

		if (separator == NULL) {
			fprintf(stderr, "Invalid key/value format in config file\r\n");
			break;
		}

		*separator = 0;
		value = separator + 1;

		size_t value_length = length - strlen(key) - 1;

		for (size_t position = 0; position < value_length; ++position) {
			if (value[position] == '\r' || value[position] == '\n') {
				value[position] = 0;
				break;
			}
		}

		printf("Key: %s - Value: %s - Length: %i\r\n", key, value, strlen(value));

		if (strcmp(key, "api_key") == 0 && strlen(value) == API_KEY_SIZE - 1) {
			strcpy(_config->api_key_, value);
		} else if (strcmp(key, "box_id") == 0 && strlen(value) == BOX_ID_SIZE - 1) {
			strcpy(_config->box_id_, value);
		} else if (strcmp(key, "temperature_id") == 0 && strlen(value) == SENSOR_ID_SIZE - 1) {
			strcpy(_config->temperature_id_, value);
		} else if (strcmp(key, "humidity_id") == 0 && strlen(value) == SENSOR_ID_SIZE - 1) {
			strcpy(_config->humidity_id_, value);
		} else if (strcmp(key, "pressure_id") == 0 && strlen(value) == SENSOR_ID_SIZE - 1) {
			strcpy(_config->pressure_id_, value);
		} else {
			fprintf(stderr, "Unknown / invalid key\r\n");
			_config->valid_ = false;
		}
	}

	fclose(file);

	return 0;
}