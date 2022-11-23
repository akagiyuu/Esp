#include "Sensor.h"
#include <IO.h>
#include <cstdlib>

using namespace Sensor;

Manager::Manager()
{
	Sensor::Health::init();
	Sensor::Motion::init();
    this->health_data = { .heart_rate = 0, .spo2 = 0 };
}
bool Manager::sync()
{
	bool is_health_read_successful = Health::read(&this->health_data);
	bool is_motion_read_successful = Motion::read(&this->motion_data);

	return is_health_read_successful || is_motion_read_successful;
}
