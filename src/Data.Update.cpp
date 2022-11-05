#include "Data.h"
#include "json/FirebaseJson.h"
#include <Arduino.h>
#include <FirebaseHelper.h>
#include <DeviceInfo.h>
#include <Log.h>
#include <Health.h>
#include <cstdlib>
#include <Convert.h>
#include "Health.h"

#define BUFFER_SIZE 100

char buffer[BUFFER_SIZE];

bool try_read_until(char terminator)
{
	size_t length = Serial.readBytesUntil(terminator, buffer, BUFFER_SIZE);
	if (length == 0)
		return false;

	return true;
}

void Data::init()
{
	for (size_t i = 0; i < 3; ++i)
		Values.set(Keys[i], 0);
	// Data::AbnormalConditions.key = base + "/Abnormal conditions";

	// Convert::to_json(Health::AbnormalCondition, AbnormalConditions.data);
}

bool Data::update()
{
	static const char terminator = ',';
	if (!Serial.available()) {
		return false;
	}

	for (int i = 0; i < 2; ++i) {
		if (!try_read_until(terminator))
			return false;
		Values.set(Keys[i], atoi(buffer));
		Serial.println(atoi(buffer));
	}

	return true;
}
