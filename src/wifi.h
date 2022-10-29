#pragma once
#include <Arduino.h>
#include "WiFiManager.h"

namespace WifiHelper
{
	void init(WiFiManager *wifi_manager);
	String default_parameter();
};
