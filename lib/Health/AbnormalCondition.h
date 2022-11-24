#pragma once
#include <Arduino.h>
#include <Sensor.h>

namespace AbnormalCondition
{
	enum Conditions {
        UnsualHeartRate = 1,
        UnsualSPO2 = 2
	};
	uint32 detect(const Sensor::Manager &sensor_manager);
}
