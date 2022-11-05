#include "Convert.h"

void Convert::to_string(FirebaseData *data_object, char *output)
{
	sprintf(output, "Path: %s, Type: %s", data_object->dataPath().c_str(), data_object->dataType().c_str());
}
