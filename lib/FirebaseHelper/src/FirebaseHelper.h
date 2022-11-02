#pragma once
#include "WString.h"
#include <Firebase_ESP_Client.h>

namespace FirebaseHelper
{
	void auth(bool is_sign_up_needed);
	namespace Conversion
	{
		void array_to_json(const char **array, size_t length, FirebaseJson &output);
		void data_to_string(FirebaseData *data_object, char *output);
	};
};
