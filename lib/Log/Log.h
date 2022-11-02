#pragma once
#include <Arduino.h>

namespace Log
{
	template <typename T> void Info(T data)
	{
		Serial.print("Info: ");
		Serial.println(data);
	}
	template <typename T> void Error(T data)
	{
		Serial.print("Error: ");
		Serial.println(data);
	}
};
