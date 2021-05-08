#ifndef SENSEBOX_COMMON_H
#define SENSEBOX_COMMON_H

// C
#include <math.h>
#include <stdbool.h>

#define API_KEY_SIZE 65
#define BOX_ID_SIZE 25
#define SENSOR_ID_SIZE 25

enum {
	kSensorTemperature = 0,
	kSensorHumidity,
	kSensorPressure,

	kSensorSize
};

struct config {
	bool valid_;

	char api_key_[API_KEY_SIZE];

	char box_id_[BOX_ID_SIZE];

	char temperature_id_[SENSOR_ID_SIZE];
	char humidity_id_[SENSOR_ID_SIZE];
	char pressure_id_[SENSOR_ID_SIZE];
};

struct data {
	bool valid_;

	double_t temperature_;
	double_t humidity_;
	double_t pressure_;
};

#endif
