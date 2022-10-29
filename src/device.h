#pragma once
#include "Arduino.h"

class Device {
    public:
    static String get_mac_address();
	static void get_auth_data(String *email, String *password);
};
