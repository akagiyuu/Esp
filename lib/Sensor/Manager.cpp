#include "Sensor.h"
#include "json/FirebaseJson.h"
#include <cstdlib>
#include <AbnormalCondition.h>

using namespace Sensor;

void Manager::init()
{
	Sensor::Health::init();
	Sensor::Motion::init();
	this->health_data = { .heart_rate = 0, .spo2 = 0 };
}
bool Manager::sync()
{
	bool is_health_read_successful = Health::read(&this->health_data);
	bool is_motion_read_successful = Motion::read(&this->motion_data);
	if (is_motion_read_successful) {
		Serial.println("Gyro:");
		Serial.println(this->motion_data.gyro.x);
		Serial.println(this->motion_data.gyro.y);
		Serial.println(this->motion_data.gyro.z);
		Serial.println("Acel:");
		Serial.println(this->motion_data.acceleration.x);
		Serial.println(this->motion_data.acceleration.y);
		Serial.println(this->motion_data.acceleration.z);
	}

	return is_health_read_successful || is_motion_read_successful;
}

void Manager::to_json(FirebaseJson &output)
{
	int32_t heart_rate = this->health_data.heart_rate;
	int32_t spo2 = this->health_data.spo2;
	output.set("Heart rate", heart_rate);
	output.set("SP O2", spo2);
    int abnormal_condition = AbnormalCondition::detect(heart_rate, spo2);
    Serial.println(abnormal_condition);
    Serial.println(heart_rate);
    Serial.print(", ");
    Serial.println(spo2);
	output.set("Abnormal conditions", abnormal_condition);
    Serial.print("Condition: ");

	FirebaseJson gyro, acceleration;
	gyro.set("x", this->motion_data.gyro.x);
	gyro.set("y", this->motion_data.gyro.y);
	gyro.set("z", this->motion_data.gyro.z);
	acceleration.set("x", this->motion_data.acceleration.x);
	acceleration.set("y", this->motion_data.acceleration.y);
	acceleration.set("z", this->motion_data.acceleration.z);

	output.set("Gyro", gyro);
	output.set("Acceleration", acceleration);
}

void Manager::print()
{
	Serial.printf("Heart rate: %d\n", this->health_data.heart_rate);
	Serial.printf("SP O2: %d\n", this->health_data.spo2);
}
