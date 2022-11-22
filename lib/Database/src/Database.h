#pragma once
#include "WString.h"
#include <Firebase_ESP_Client.h>
#include <Sensor.h>

namespace Database
{
    extern FirebaseData DataObject;
	void auth(bool is_sign_up_needed);
    bool send(struct Sensor::Data *sensor_data);
}
