#include "firebase.h"
#include <Arduino.h>
#include "wifi.h"
#include <Firebase_ESP_Client.h>
#include "env.h"
#include "addons/TokenHelper.h"
#include "device.h"

namespace FirebaseHelper
{
	FirebaseConfig config;
	FirebaseAuth auth;

	bool sign_up(String *email, String *password)
	{
		if (is_signed_up != true) {
			if (Firebase.signUp(&config, &auth, email, MacAdress)) {
				Serial.println("ok");
				EEPROM.write(0, 1);
				EEPROM.commit();
			} else {
				Serial.printf("%s\n",
					config.signer.signupError.message
						.c_str());
			}
		} else {
			auth.user.email = email;
			auth.user.password = MacAdress;
		}
	}
	void init(bool is_signed_up)
	{
		String email;
		String password;

        Device::get_auth_data(&email, &password);

		config.api_key = ApiKey;
		sign_up(email, password);
		config.database_url = DatabaseURL;

		/* Assign the callback function for the long running token generation task */
		config.token_status_callback = tokenStatusCallback;

		Firebase.begin(&config, &auth);

		Firebase.reconnectWiFi(true);
	}

}
