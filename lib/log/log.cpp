#include "log.h"
#include <Arduino.h>

template <typename T> void Log::Info(T data) {
    Serial.println(data);
}
template <typename T> void Log::Error(T data) {
    Serial.println(data);
}
