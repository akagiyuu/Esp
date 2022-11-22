#pragma once
#include <Arduino.h>
#include <Firebase_ESP_Client.h>

namespace Convert
{
	template <size_t length> void to_json(const char *(&array)[length], FirebaseJson &output)
	{
		for (size_t i = 0; i < length; ++i)
			output.set(array[i], 0);
	}
	void to_string(FirebaseData *data_object, char *output);
}
