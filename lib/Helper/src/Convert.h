#pragma once
#include "Sensor.h"
#include <Arduino.h>
#include <Firebase_ESP_Client.h>

namespace Convert
{
    void to_json(const Sensor::Manager &sensor_manager, FirebaseJson &output);
	void to_string(FirebaseData *data_object, char *output);
}
