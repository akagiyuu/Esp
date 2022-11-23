#include "Sensor.h"
#include <IO.h>
#include <cstdlib>

// #define BUFFER_SIZE 100
//
// char buffer[BUFFER_SIZE];

// bool Sensor::read(struct Data *sensor_data)
// {
// 	static const char terminator = ',';
// 	if (!Serial.available()) {
// 		return false;
// 	}
//
// 	if (!IO::try_read_until(buffer, BUFFER_SIZE, terminator))
// 		return false;
//     sensor_data->heart_rate = atoi(buffer);
//
// 	if (!IO::try_read_until(buffer, BUFFER_SIZE, terminator))
// 		return false;
//     sensor_data->spo2 = atoi(buffer);
//     Serial.print(sensor_data->heart_rate);
//     Serial.print(",");
//     Serial.println(sensor_data->spo2);
//
// 	return true;
// };
void Sensor::init()
{
    Sensor::Health::init();
}
bool Sensor::read(struct Sensor::Data *sensor_data)
{
	static Health::Data health_data = { .heart_rate = 0, .spo2 = 0 };
    if(!Health::read(&health_data))
        return false;

    sensor_data->spo2 = health_data.spo2;
    sensor_data->heart_rate = health_data.heart_rate;

    return true;
}