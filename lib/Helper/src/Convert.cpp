#include "Convert.h"
#include <Sensor.h>
#include <AbnormalCondition.h>

void Convert::to_string(FirebaseData *data_object, char *output)
{
	sprintf(output, "Path: %s, Type: %s", data_object->dataPath().c_str(), data_object->dataType().c_str());
}

void Convert::to_json(const Sensor::Manager &sensor_manager, FirebaseJson &output)
{
    int32_t heart_rate = sensor_manager.health_data.heart_rate;
    int32_t spo2 = sensor_manager.health_data.spo2;
	output.set("Heart rate", heart_rate);
	output.set("SP O2", spo2);
	output.set("Abnormal conditions", AbnormalCondition::detect(heart_rate, spo2));
}
