#include "config.h"

// C
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t config_parseFromFile(const char* _fullpath, struct config* _config)
{
	int32_t return_value = 0;

	FILE* file;
	size_t length;
	char* buffer;

	errno = 0;

	file = fopen(_fullpath, "r");

	if (!file) {
		fprintf(stderr, "Unable to open config file (%s)\r\n", strerror(errno));
		return 1;
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);

	buffer = malloc(length);

	if (buffer) {
		fread(buffer, 1, length, file);
		return_value = config_parse(buffer, length, _config);
		free(buffer);
	}

	fclose(file);

	return return_value;
}

int32_t config_parse(char* _data, size_t _data_size, struct config* _config)
{
	int32_t return_value = 0;

	size_t position = 0;

	char* key;
	char* separator;
	char* value;
	char* start;
	char* end;

	_config->valid_ = true;
	memset(_config->api_key_, 0, API_KEY_SIZE);
	memset(_config->box_id_, 0, BOX_ID_SIZE);
	memset(_config->temperature_id_, 0, SENSOR_ID_SIZE);
	memset(_config->humidity_id_, 0, SENSOR_ID_SIZE);
	memset(_config->pressure_id_, 0, SENSOR_ID_SIZE);

	start = _data;

	while (position < _data_size) {
		key = start;
		separator = strchr(key, '=');

		if (separator == NULL) {
			fprintf(stderr, "Invalid key/value format in config file\r\n");
			return_value = 1;
			break;
		}

		*separator = 0;
		value = separator + 1;

		end = strchr(value, '\n');

		if (end == NULL) {
			fprintf(stderr, "Missing line ending in config file\r\n");
			return_value = 1;
			break;
		}

		*end = 0;

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
			return_value = 1;
			break;
		}

		position += strlen(key);
		position += strlen(value);
		position += 2;

		start = end + 1;
	}

	return return_value;
}