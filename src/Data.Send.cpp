#include "Data.h"
#include "json/FirebaseJson.h"
#include <Arduino.h>
#include <FirebaseHelper.h>
#include <DeviceInfo.h>
#include <Log.h>
#include <Health.h>
#include <cstdlib>
#include <map>

void firebase_set_error_handler(FirebaseData *data_object)
{
	Log::Error(data_object->errorReason());
}

	// template <size_t length> void to_json(const char *(&array)[length], FirebaseJson &output)
template <typename T, size_t length> void send(String (&array)[length])
{
	for (auto const &[key, value] : health_entry) {
		Serial.print("Updating: ");
		Serial.println(key);
		if (!Firebase.RTDB.set(&Data::DataObject, key, value))
			firebase_set_error_handler(&Data::DataObject);
	}
}

bool Data::send()
{
	while (!Firebase.ready())
		;

	send(Data::Keys);
	// send(&Data::AbnormalConditions);

	return true;
}
