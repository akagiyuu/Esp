#pragma once
#include <Firebase_ESP_Client.h>

namespace Data
{
	extern FirebaseData DataObject;
	extern FirebaseJson HealthData;
	extern FirebaseJson AbnormalConditions;
	void init();
	bool update();
	bool send();
	void send(String &ref, FirebaseJson *data);
}
