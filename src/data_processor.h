#include <Arduino.h>
#include <cstdlib>

#define BUFFER_SIZE 100
char buffer[BUFFER_SIZE];

namespace Data
{
	bool read_until(char terminator, int *output)
	{
		size_t length = Serial.readBytesUntil(terminator, buffer, BUFFER_SIZE);
		if (length <= 0) {
			return false;
		}

		*output = atoi(buffer);
		return true;
	}
	bool read(size_t n, char terminator, int *array)
	{
		bool is_success = true;
		for (size_t i = 0; i < n; ++i) {
			is_success |= read_until(terminator, &array[i]);
		}

		return is_success;
	}

}
