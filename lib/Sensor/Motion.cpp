#include "Sensor.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

using namespace Sensor;

Adafruit_MPU6050 MotionSensor;

void Motion::init()
{
	if (!MotionSensor.begin()) {
		Serial.println("Failed to find MPU6050 chip");
		while (true) {
			delay(10);
		}
	}
	Serial.println("MPU6050 Found!");

	MotionSensor.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
	MotionSensor.setMotionDetectionThreshold(1);
	MotionSensor.setMotionDetectionDuration(20);
	MotionSensor.setInterruptPinLatch(true); // Keep it latched.  Will turn off when reinitialized.
	MotionSensor.setInterruptPinPolarity(true);
	MotionSensor.setMotionInterrupt(true);
}

bool Motion::read(struct Motion::Data *motion_data)
{
	if (!MotionSensor.getMotionInterruptStatus())
		return false;
	/* Get new sensor events with the readings */
	sensors_event_t accel_event, gyro_event, temp_event;
	MotionSensor.getEvent(&accel_event, &gyro_event, &temp_event);

    motion_data->acceleration = accel_event.acceleration;
    motion_data->gyro = gyro_event.acceleration;

	/* Print out the values */
	// Serial.print("AccelX:");
	// Serial.print(accel_event.acceleration.x);
	// Serial.print(",");
	// Serial.print("AccelY:");
	// Serial.print(accel_event.acceleration.y);
	// Serial.print(",");
	// Serial.print("AccelZ:");
	// Serial.print(accel_event.acceleration.z);
	// Serial.print(", ");
	// Serial.print("GyroX:");
	// Serial.print(gyro_event.gyro.x);
	// Serial.print(",");
	// Serial.print("GyroY:");
	// Serial.print(gyro_event.gyro.y);
	// Serial.print(",");
	// Serial.print("GyroZ:");
	// Serial.print(gyro_event.gyro.z);
	// Serial.println("");
	//
	return true;
}
