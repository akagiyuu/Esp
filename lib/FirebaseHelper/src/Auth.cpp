#include "FirebaseHelper.h"
#include <Arduino.h>
#include "wifi_helper.h"
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include "device_info.h"
#include <EEPROM.h>
#include <log.h>
#include "env.h"

FirebaseAuth auth;
FirebaseConfig config;

namespace FirebaseHelper
{
	namespace Auth
	{
		bool sign_up(String *email, String *password)
		{
			Log::Info("sign_up");
			bool is_success = Firebase.signUp(&config, &auth, *email, *password);

			if (is_success) {
				EEPROM.write(0, 0);
				EEPROM.commit();
			}

			return is_success;
		}
		void sign_in(String *email, String *password)
		{
			auth.user.email = *email;
			auth.user.password = *password;
		}
		void init(bool is_sign_up_needed)
		{
			String email;
			String password;

			DeviceInfo::get_auth_data(&email, &password);
			::Log::Info(is_sign_up_needed);

			config.api_key = API_KEY;
			config.database_url = DATABASE_URL;
			if (is_sign_up_needed) {
				if (!sign_up(&email, &password)) {
					Serial.println(config.signer.signupError.message.c_str());
				}
			} else {
				sign_in(&email, &password);
			}

			config.token_status_callback = tokenStatusCallback;

			Firebase.begin(&config, &auth);

			Firebase.reconnectWiFi(true);
		}

	}
}
