#include "AbnormalCondition.h"
#include "Sensor.h"

uint detect_health(int32_t heart_rate, int32_t spo2)
{
	uint32 conditions = 0;
	if (heart_rate < 60 || heart_rate > 100)
		conditions |= AbnormalCondition::UnsualHeartRate;
	if (spo2 > 90)
		conditions |= AbnormalCondition::UnsualSPO2;

	return conditions;
}
uint32 AbnormalCondition::detect(const Sensor::Manager &sensor_manager)
{
	uint32 conditions = detect_health(sensor_manager.health_data.heart_rate, sensor_manager.health_data.spo2);

	return conditions;
}
