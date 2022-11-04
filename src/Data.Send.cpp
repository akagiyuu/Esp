#include "Data.h"
#include "json/FirebaseJson.h"
#include <Arduino.h>
#include <FirebaseHelper.h>
#include <DeviceInfo.h>
#include <Log.h>
#include <Health.h>
#include <cstdlib>

void firebase_set_error_handler(FirebaseData *data_object)
{
	Log::Error(data_object->errorReason());
}

void Data::send(String &ref, FirebaseJson *data)
{
    Serial.print("Updating: ");
    Serial.println(ref);
	if (!Firebase.RTDB.updateNode(&DataObject, ref, data))
		firebase_set_error_handler(&DataObject);
}

bool Data::send()
{
	static String health_ref = DeviceInfo::get_mac_address();
	static String abnormal_conditions_ref = DeviceInfo::get_mac_address() + "/Abnormal conditions";
	while (!Firebase.ready())
		;


	send(health_ref, &HealthData);
	send(abnormal_conditions_ref, &AbnormalConditions);

    return true;
}
