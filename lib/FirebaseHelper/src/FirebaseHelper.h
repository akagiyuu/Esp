#pragma once
#include "WString.h"
#include <Firebase_ESP_Client.h>

namespace FirebaseHelper
{
	void auth(bool is_sign_up_needed);
	namespace Conversion
	{
		template <size_t length> void array_to_json(const char *(&array)[length], FirebaseJson &output)
		{
			for (size_t i = 0; i < length; ++i)
				output.set(array[i], 0);
		}
		void data_to_string(FirebaseData *data_object, char *output);
	}
}
