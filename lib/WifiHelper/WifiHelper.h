#pragma once
#include <Arduino.h>
#include "WiFiManager.h"

class WifiHelper
{
    public:
	static void init(WiFiManager *wifi_manager);
	static String default_parameter();
};
