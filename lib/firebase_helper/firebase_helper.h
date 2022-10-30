#pragma once
#include "Firebase_ESP_Client.h"

typedef String string;

namespace FirebaseHelper
{
	void init(bool is_signed_up,
		const char *api_key,
		const char *database_url);

	bool sign_up(string *email, string *password);
	void sign_in(string *email, string *password);

    void log(FirebaseData *data_object);
};
