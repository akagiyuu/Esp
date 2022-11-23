#include "Sensor.h"
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Database.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <EEPROM.h>
#include <Internet.h>
#include <addons/RTDBHelper.h>
#include <DeviceInfo.h>

#define EEPROM_SIZE 1

struct Sensor::Data sensor_data = { .heart_rate = 0, .spo2 = 0, .velocity = 0, .altitude = 0 };

void setup()
{
	EEPROM.begin(EEPROM_SIZE);
	Serial.begin(115200);
	Serial.println();
	Serial.println();

	Internet::init();

	int is_sign_up_needed = EEPROM.read(0);
	Serial.println(is_sign_up_needed);

	Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
	Database::auth(is_sign_up_needed);
}

void loop()
{
	if (Sensor::read(&sensor_data))
		Database::send(&sensor_data);
}
