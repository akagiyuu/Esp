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
#include <Sensor.h>

#define EEPROM_SIZE 1

Sensor::Manager SensorManager;

#define BUTTON 8

void setup()
{
	EEPROM.begin(EEPROM_SIZE);
	Serial.begin(115200);
	Serial.println();
	Serial.println();
	pinMode(BUTTON, INPUT);

	Internet::init();

	int is_sign_up_needed = EEPROM.read(0);
	Serial.println(is_sign_up_needed);

	Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
	Database::auth(is_sign_up_needed);
	SensorManager.init();
}

void loop()
{
	if (digitalRead(BUTTON) == HIGH)
		Serial.println("Button pushed");
	if (SensorManager.sync())
		Database::send(SensorManager);
}
