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
#include <env.h>
#include "data_processor.h"

#include <addons/RTDBHelper.h>

#define EEPROM_SIZE 1

WiFiManager wifi_manager;

unsigned long sendDataPrevMillis = 0;
int ran1 = 0;
int ran2 = 0;
int ran3 = 0;
int ran4 = 0;

boolean read_and_parse_serial_data()
{
	if (!Serial.available()) {
		return false;
	}
    int output[4];
    Data::read(4, ',', output);

	return true;
}
void setup()
{
	EEPROM.begin(EEPROM_SIZE);
	Serial.begin(115200);
	Serial.println();
	Serial.println();

	WifiHelper::init(&wifi_manager);

	int is_signed_up = EEPROM.read(0);
	Serial.println(is_signed_up);

	// Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
	FirebaseHelper::init(is_signed_up, ApiKey, DatabaseURL);
}

void loop()
{
}
