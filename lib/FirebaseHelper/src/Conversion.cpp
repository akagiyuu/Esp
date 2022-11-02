#include "FirebaseHelper.h"
#include <cstdio>

namespace FirebaseHelper
{
	namespace Conversion
	{
		void array_to_json(const char **array, size_t length, FirebaseJson &output)
		{
			for (size_t i = 0; i < length; ++i) {
				output.set(i, array[i]);
			}
		}
		void data_to_string(FirebaseData *data_object, char *output)
		{
			sprintf(output,
				"Path: %s, Type: %s",
				data_object->dataPath().c_str(),
				data_object->dataType().c_str());
		}
	}
}
