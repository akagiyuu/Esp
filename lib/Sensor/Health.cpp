#include "Sensor.h"
#include <MAX30105.h>
#include "spo2_algorithm.h"
#include <Array.h>

using namespace Sensor;

#define BUFFER_SIZE 100
#define SAMPLE_PER_CALCULATE 25
#define READ_LED 13

static uint32_t IrBuffer[BUFFER_SIZE]; // infrared LED sensor data
static uint32_t RedBuffer[BUFFER_SIZE]; // red LED sensor data
MAX30105 health_sensor;

void read_raw(byte sample_index)
{
	while (health_sensor.available() == false)
		health_sensor.check();

	digitalWrite(READ_LED, !digitalRead(READ_LED));

	RedBuffer[sample_index] = health_sensor.getRed();
	IrBuffer[sample_index] = health_sensor.getIR();
	health_sensor.nextSample();
	//
	// Serial.print("Ir: ");
	// Serial.print(IrBuffer[sample_index]);
	// Serial.print(", Red: ");
	// Serial.println(RedBuffer[sample_index]);
}

void Health::init()
{
	for (byte i = 0; i < 100; i++) {
		read_raw(i);
	}
}
bool Health::read(struct Data *health_data)
{
	Array::shift_left(IrBuffer, SAMPLE_PER_CALCULATE);
	Array::shift_left(RedBuffer, SAMPLE_PER_CALCULATE);

	for (byte i = 100 - SAMPLE_PER_CALCULATE; i < 100; i++) {
		read_raw(i);
	}
	int8_t is_valid_spo2, is_valid_heart_rate;

	// After gathering 25 new samples recalculate HR and SP02
	maxim_heart_rate_and_oxygen_saturation(IrBuffer,
		BUFFER_SIZE,
		RedBuffer,
		&(health_data->spo2),
		&is_valid_spo2,
		&(health_data->heart_rate),
		&is_valid_heart_rate);

	return is_valid_heart_rate && is_valid_spo2;
}
