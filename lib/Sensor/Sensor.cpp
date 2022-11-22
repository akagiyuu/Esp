#include "Sensor.h"

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];

bool Sensor::read(struct Data *sensor_data)
{
	static const char terminator = ',';
	if (!Serial.available()) {
		return false;
	}

	if (!Helper::try_read_until(terminator))
		return false;

	return true;
};
