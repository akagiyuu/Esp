#pragma once
#include <Firebase_ESP_Client.h>

namespace Data
{
    extern String Keys[3];
    extern FirebaseJson Values;
	extern FirebaseData DataObject;
	void init();
	bool update();
	bool send();
}
