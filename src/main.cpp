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

#define EEPROM_SIZE 1

WiFiManager WifiManager;
FirebaseData DataObject;
int output[4];

const char *ApiKey = "";
const char *DatabaseURL = "";

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

	int is_signed_up = EEPROM.read(0);
	Serial.println(is_signed_up);

	Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
	FirebaseHelper::init(is_signed_up, ApiKey, DatabaseURL);
}

void firebase_set_error_handler(FirebaseData *data_object) {
    Log::Error(data_object->errorReason());
}

void loop()
{
    if(!Firebase.ready() || !read_and_parse_serial_data())
        return;

    if(!Firebase.RTDB.setInt(&DataObject, "Test/Oxygen level", output[0]))
        firebase_set_error_handler(&DataObject);
}
