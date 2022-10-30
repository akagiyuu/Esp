#include "firebase_helper.h"
#include <Arduino.h>
#include "wifi_helper.h"
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include "device_info.h"
#include <EEPROM.h>

FirebaseData fbdo;
FirebaseData stream;
FirebaseAuth auth;
FirebaseConfig config;

namespace FirebaseHelper
{
	bool sign_up(string *email, string *password)
	{
		bool is_success = Firebase.signUp(&config, &auth, *email, *password);

		if (is_success) {
			EEPROM.write(0, 1);
			EEPROM.commit();
		}

		return is_success;
	}
	void sign_in(string *email, string *password)
	{
		auth.user.email = *email;
		auth.user.password = *password;
	}
	void init(bool is_signed_up, const char *api_key, const char *database_url)
	{
		string email;
		string password;

		DeviceInfo::get_auth_data(&email, &password);

		config.api_key = api_key;
		config.database_url = database_url;
		if (!is_signed_up && !sign_up(&email, &password)) {
			Serial.println(config.signer.signupError.message.c_str());
		}

		config.token_status_callback = tokenStatusCallback;

		Firebase.begin(&config, &auth);

		Firebase.reconnectWiFi(true);
	}
	// if (Firebase.RTDB.setInt(&fbdo, +"/Oxygen_Level", ran1)) {
	// 		Serial.println("PASSED");
	// 		Serial.println("PATH: " + fbdo.dataPath());
	// 		Serial.println("TYPE: " + fbdo.dataType());
	// 	} else {
	// 		Serial.println("FAILED");
	// 		Serial.println("REASON: " + fbdo.errorReason());
	// 	}

	template <int> void set(FirebaseData data_object, string path, int data)
	{
	}
}
