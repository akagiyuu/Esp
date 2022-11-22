#include "Data.h"
#include <Arduino.h>
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
	Serial.println(data_object->errorReason());
}

bool Data::send()
{
    static String base = DeviceInfo::get_mac_address();
	while (!Firebase.ready())
		;

    Serial.printf("Sending to database at key: %s\n", base.c_str());
    if(!Firebase.RTDB.updateNode(&DataObject, base, &Values)) {
        firebase_set_error_handler(&DataObject);
        return false;
    }

	return true;
}
