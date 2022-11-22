#include "WifiHelper.h"
#include "WiFiManager.h"
#include "DeviceInfo.h"
#include <cstdio>

String WifiHelper::default_parameter()
{
	String mac_address = DeviceInfo::get_mac_address();

	String display = "<p>Your ID: " + mac_address + "</p>";

	return display;
}

void WifiHelper::init()
{
	WiFiManager wifi_manager;

	String parameter = WifiHelper::default_parameter();

	WiFiManagerParameter custom_text((const char *)parameter.c_str());

	wifi_manager.resetSettings();

	wifi_manager.addParameter(&custom_text);
	wifi_manager.autoConnect("WING's WiFi Manager");
	Serial.println("connected :)");
}
