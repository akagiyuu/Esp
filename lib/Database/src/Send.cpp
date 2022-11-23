#include "Convert.h"
#include "Database.h"
#include <Arduino.h>
#include "Sensor.h"
#include "json/FirebaseJson.h"
#include <Arduino.h>
#include <DeviceInfo.h>
#include <cstdlib>

void firebase_set_error_handler(FirebaseData *data_object)
{
	Serial.println(data_object->errorReason());
}

bool Database::send(const Sensor::Manager &sensor_manager)
{
    static String base = DeviceInfo::get_mac_address();
    static FirebaseJson firebase_data;
	while (!Firebase.ready())
		;

    Convert::to_json(sensor_manager, firebase_data);

    Serial.printf("Sending to database at key: %s\n", base.c_str());
    if(!Firebase.RTDB.updateNode(&DataObject, base, &firebase_data)) {
        firebase_set_error_handler(&DataObject);
        return false;
    }

	return true;
}
