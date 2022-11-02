#pragma once
#include "WString.h"
#include <Firebase_ESP_Client.h>

namespace FirebaseHelper
{
	namespace Auth
	{
		void init(bool is_sign_up_needed);

		bool sign_up(String *email, String *password);
		void sign_in(String *email, String *password);
	};
	namespace Conversion
	{
		void array_to_json(const char **array, size_t length, FirebaseJson &output);
		void data_to_string(FirebaseData *data_object, char *output);
	};
};
