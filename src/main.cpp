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

#include <addons/RTDBHelper.h>
/* 2. Define the API Key */

/* 3. Define the RTDB URL */

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
	String rxString = "";
	String strArr[4]; // Set the size of the array to equal the number of values you will be receiveing.

	// Keep looping until there is something in the buffer.
	while (Serial.available()) {
		delay(2);
		// Delay to allow byte to arrive in input buffer.

		// Read a single character from the buffer.
		char ch = Serial.read();
		// Append that single character to a string.
		rxString += ch;
	}

	int stringStart1 = 0;
	int dataStorage = 0;
	for (int i = 0; i < rxString.length(); i++) {
		// Get character and check if it's our "special" character.
		/* Chỗ này là mặc định sẽ lấy phần String từ dấu , trở lên có thể thay dấu , bằng cái khác giả sử như là dấu .
    hoặc kí tự A, B, C, D*/
		if (rxString.charAt(i) == ',') {
			// Clear previous values from array.
			strArr[dataStorage] = "";
			// Save substring into array.
			strArr[dataStorage] = rxString.substring(stringStart1, i);
			// Set new string starting point.
			stringStart1 = (i + 1);
			dataStorage += 1;
		}
	}
	String x1 = strArr[0];
	String y1 = strArr[1];
	String x2 = strArr[2];
	String y2 = strArr[3];
	ran1 = x1.toInt();
	ran2 = y1.toInt();
	ran3 = x2.toInt();
	ran4 = y2.toInt();
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
