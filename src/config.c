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
	int32_t return_value = 1;

	char key[100];
	char value[100];

	char* start;
	char* end;

	// Reset config structure to default values

	_config->valid_ = false;

	_config->api_key_valid_ = false;
	_config->box_id_valid_ = false;
	_config->temperature_id_valid_ = false;
	_config->humidity_id_valid_ = false;
	_config->pressure_id_valid_ = false;

	memset(_config->api_key_, 0, API_KEY_SIZE);
	memset(_config->box_id_, 0, BOX_ID_SIZE);
	memset(_config->temperature_id_, 0, SENSOR_ID_SIZE);
	memset(_config->humidity_id_, 0, SENSOR_ID_SIZE);
	memset(_config->pressure_id_, 0, SENSOR_ID_SIZE);

	// Set running parsing variable to the beginning of the data buffer
	start = _data;

	while (sscanf(start, "%99[^=]%*c%99[^\r\n]%*c", key, value) == 2) {
		printf("Key: %s - Value: %s\r\n", key, value);

		if (strcmp(key, "api_key") == 0 && strlen(value) == API_KEY_SIZE - 1) {
			strcpy(_config->api_key_, value);
			_config->api_key_valid_ = true;
		} else if (strcmp(key, "box_id") == 0 && strlen(value) == BOX_ID_SIZE - 1) {
			strcpy(_config->box_id_, value);
			_config->box_id_valid_ = true;
		} else if (strcmp(key, "temperature_id") == 0 && strlen(value) == SENSOR_ID_SIZE - 1) {
			strcpy(_config->temperature_id_, value);
			_config->temperature_id_valid_ = true;
		} else if (strcmp(key, "humidity_id") == 0 && strlen(value) == SENSOR_ID_SIZE - 1) {
			strcpy(_config->humidity_id_, value);
			_config->humidity_id_valid_ = true;
		} else if (strcmp(key, "pressure_id") == 0 && strlen(value) == SENSOR_ID_SIZE - 1) {
			strcpy(_config->pressure_id_, value);
			_config->pressure_id_valid_ = true;
		} else {
			fprintf(stderr, "Invalid key or value\r\n");
		}

		end = strchr(start, '\n');

		// Assume that the end of the buffer is reached when no more line feeds are found

		if (end != NULL) {
			start = end + 1;
		} else {
			break;
		}
	}

	// The API-Key and the Box-ID must be set for the config to be valid

	if (!_config->api_key_valid_) {
		fprintf(stderr, "API-Key not found\r\n");
	} else if (!_config->box_id_valid_) {
		fprintf(stderr, "Box-ID not found\r\n");
	} else {
		_config->valid_ = true;
		return_value = 0;
	}

	return return_value;
}