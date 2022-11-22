#include "Helper.h"
#include <Arduino.h>

bool Helper::try_read_until(char *buffer, int length, char terminator)
{
	if (Serial.readBytesUntil(terminator, buffer, length) == 0)
		return false;

	return true;
}
