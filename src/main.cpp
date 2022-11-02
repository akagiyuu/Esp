#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <firebase_helper.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <EEPROM.h>
#include <wifi_helper.h>
#include "data_processor.h"
#include "log.h"
#include <addons/RTDBHelper.h>
#include "device_info.h"

#define EEPROM_SIZE 1

WiFiManager WifiManager;
FirebaseData DataObject;
FirebaseJson health;
FirebaseJson abnormal_conditions;
int output[4];

boolean read_and_parse_serial_data()
{
	if (!Serial.available()) {
		return false;
	}
	Data::read(4, ',', output);

	return true;
}
void setup()
{
	EEPROM.begin(EEPROM_SIZE);
	Serial.begin(115200);
	Serial.println();
	Serial.println();

	WifiHelper::init(&WifiManager);

	int is_sign_up_needed = EEPROM.read(0);
	Serial.println(is_sign_up_needed);

	Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
	FirebaseHelper::init(is_sign_up_needed);

    health.set("SP O2", 10);
    health.set("Heart rate", 20);
    const char *data[] = {"opk", "test"};
    FirebaseHelper::array_to_json(data, 2, abnormal_conditions);
}

void firebase_set_error_handler(FirebaseData *data_object)
{
	Log::Error(data_object->errorReason());
}

void loop()
{
	if (!Firebase.ready() || !read_and_parse_serial_data())
		return;

	if(!Firebase.RTDB.updateNode(&DataObject, DeviceInfo::get_mac_address(), &health))
	    firebase_set_error_handler(&DataObject);
    if(!Firebase.RTDB.updateNode(&DataObject, DeviceInfo::get_mac_address() + "/Abnormal conditions", &abnormal_conditions))
	    firebase_set_error_handler(&DataObject);
}
