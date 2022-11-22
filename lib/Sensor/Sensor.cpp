#include "Sensor.h"
#include <IO.h>

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];

bool Sensor::read(struct Data *sensor_data)
{
	static const char terminator = ',';
	if (!Serial.available()) {
		return false;
	}

	if (IO::try_read_until(buffer, BUFFER_SIZE, terminator))
		return false;

	return true;
};
