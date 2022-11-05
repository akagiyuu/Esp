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
	String base = DeviceInfo::get_mac_address();
    Data::Health = {
	    { base + "/Heart rate", 10 },
	    { base + "/SP O2", 10 },
	    { base + "/Abnormal conditions", 2 },
    };
	// Data::AbnormalConditions.key = base + "/Abnormal conditions";

	// Convert::to_json(Health::AbnormalCondition, AbnormalConditions.data);
}

bool Data::update()
{
	static const char terminator = ',';
	if (!Serial.available()) {
		return false;
	}

	if (!try_read_until(terminator))
		return false;
	HeartRate.data = atoi(buffer);
	Serial.println(HeartRate.data);

	if (!try_read_until(terminator))
		return false;
	SPO2.data = atoi(buffer);
	Serial.println(SPO2.data);

	return true;
}
