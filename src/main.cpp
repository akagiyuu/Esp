#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <FirebaseHelper.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <EEPROM.h>
#include <WifiHelper.h>
#include <Log.h>
#include <addons/RTDBHelper.h>
#include <DeviceInfo.h>
#include "Data.h"
#include <AbnormalCondition.h>

#define EEPROM_SIZE 1

void setup()
{
	EEPROM.begin(EEPROM_SIZE);
	Serial.begin(115200);
	Serial.println();
	Serial.println();

	WifiHelper::init();

	int is_sign_up_needed = EEPROM.read(0);
	Serial.println(is_sign_up_needed);

	Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
	FirebaseHelper::auth(is_sign_up_needed);

	Data::init();
}

void loop()
{
	if (Data::update())
		Data::send();
}
