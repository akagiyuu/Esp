#include "Convert.h"
#include <Sensor.h>
#include <AbnormalCondition.h>

void Convert::to_string(FirebaseData *data_object, char *output)
{
	sprintf(output, "Path: %s, Type: %s", data_object->dataPath().c_str(), data_object->dataType().c_str());
}

void Convert::to_json(struct Sensor::Data *sensor_data, FirebaseJson &output)
{
	output.set("Heart rate", sensor_data->heart_rate);
	output.set("SP O2", sensor_data->spo2);
	output.set("Abnormal conditions", AbnormalCondition::detect(sensor_data->heart_rate, sensor_data->spo2));
}
