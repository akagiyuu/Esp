#include "WifiHelper.h"
#include "WiFiManager.h"
#include "DeviceInfo.h"
#include <cstdio>

String WifiHelper::default_parameter()
{
	String mac_address = DeviceInfo::get_mac_address();
	char display[100];
	sprintf(display, "<p>Your ID: %s</p>", mac_address.c_str());

	return display;
}

void WifiHelper::init(WiFiManager *wifi_manager)
{
	const char *default_parameter = WifiHelper::default_parameter().c_str();

	WiFiManagerParameter custom_text(default_parameter);

	wifi_manager->resetSettings();

	wifi_manager->addParameter(&custom_text);
	wifi_manager->autoConnect("WING's WiFi Manager");
	Serial.println("connected :)");
}
