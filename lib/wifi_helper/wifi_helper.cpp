#include "wifi_helper.h"
#include "WiFiManager.h"
#include "device_info.h"

String WifiHelper::default_parameter()
{
	String mac_address = DeviceInfo::get_mac_address();

	String display = "<p>Your ID: " + mac_address + "</p>";
	String email = mac_address + "@gmail.com";

	return display;
}

void WifiHelper::init(WiFiManager *wifi_manager)
{
	String mac_address = DeviceInfo::get_mac_address();
	const char *default_parameter = WifiHelper::default_parameter().c_str();

	WiFiManagerParameter custom_text(default_parameter);

	(*wifi_manager).resetSettings();

	(*wifi_manager).addParameter(&custom_text);
	(*wifi_manager).autoConnect("WING's WiFi Manager");
	Serial.println("connected :)");
}
