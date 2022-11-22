#pragma once
#include <Arduino.h>

struct Health {
	int32_t heart_rate;
	int32_t spo2;
};

class Patient {
    public:
	Health health;
    uint32 abnormal_condition;

    void sync();
};
