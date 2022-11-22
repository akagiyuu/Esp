#pragma once
#include <Arduino.h>

namespace Sensor
{
	struct Data {
		int32_t heart_rate;
		int32_t spo2;
        int32_t velocity;
        int32_t height;
	};
	bool read(struct Data *sensor_data);
}
