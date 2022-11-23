// #include "Sensor.h"
//
// using namespace Sensor;
//
// void Motion::init()
// {
// 	if (!mpu.begin()) {
// 		Serial.println("Failed to find MPU6050 chip");
// 		while (1) {
// 			delay(10);
// 		}
// 	}
// 	Serial.println("MPU6050 Found!");
//
// 	//setupt motion detection
// 	mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
// 	mpu.setMotionDetectionThreshold(1);
// 	mpu.setMotionDetectionDuration(20);
// 	mpu.setInterruptPinLatch(true); // Keep it latched.  Will turn off when reinitialized.
// 	mpu.setInterruptPinPolarity(true);
// 	mpu.setMotionInterrupt(true);
// }
//
// bool Motion::read(struct Motion::Data *motion_data)
// {
// }
