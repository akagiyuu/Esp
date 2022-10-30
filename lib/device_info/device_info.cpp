#include "device_info.h"
#include "WiFiManager.h"

String DeviceInfo::get_mac_address()
{
	String mac_address = WiFi.macAddress();
	mac_address.replace(":", "");

	return mac_address;
}

void DeviceInfo::get_auth_data(String *email, String *password)
{
	String mac_address = get_mac_address();

	*email = mac_address + "@gmail.com";
	*password = mac_address;
};
