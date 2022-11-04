#include "Data.h"
#include "json/FirebaseJson.h"
#include <Arduino.h>
#include <FirebaseHelper.h>
#include <DeviceInfo.h>
#include <Log.h>
#include <Health.h>
#include <cstdlib>

#define BUFFER_SIZE 100
char buffer[BUFFER_SIZE];
int output[4];

bool read_until(char terminator, int *output)
{
	size_t length = Serial.readBytesUntil(terminator, buffer, BUFFER_SIZE);
	if (length <= 0) {
		return false;
	}

	*output = atoi(buffer);
	return true;
}
bool read(size_t n, char terminator, int *array)
{
	bool is_success = true;
	for (size_t i = 0; i < n; ++i) {
		is_success |= read_until(terminator, &array[i]);
	}

	return is_success;
}
bool read_and_parse_serial_data()
{
	if (!Serial.available()) {
		return false;
	}
	read(4, ',', output);

	return true;
}

void Data::init()
{
	HealthData.set("SP O2", 10);
	HealthData.set("Heart rate", 20);
	FirebaseHelper::Conversion::array_to_json(Health::AbnormalCondition, AbnormalConditions);
}

bool Data::update()
{
	return read_and_parse_serial_data();
}

