#include "Steering.h"
#include "Arduino.h"
#include "CPPM/CPPM.h"
#include "ServoTimer2/ServoTimer2.h"

Steering::Steering(Light *lights) {
	iCppmPosition = SERVO_ZERO_POSITION;
	iCppmPositionLast = SERVO_ZERO_POSITION;
	errorCounter = 0;
	ServoTimer2 sServo;

	_lights = lights;
}

int16_t Steering::convertPosition(int16_t currentValue) {
	if (currentValue) {
		return Steering::fixRange(
				map(currentValue, 0, 255, SERVO_MAX_ANGLE_LEFT,
				SERVO_MAX_ANGLE_RIGHT));
	}
	return 0;
}

int16_t Steering::fixRange(int16_t value) {
	if (value == 0)
		return iCppmPositionLast;
	if (value < SERVO_MAX_ANGLE_LEFT)
		return SERVO_MAX_ANGLE_LEFT;
	if (value > SERVO_MAX_ANGLE_RIGHT)
		return SERVO_MAX_ANGLE_RIGHT;
	return value;
}

void Steering::checkTrafficator(int16_t position) {
	if (position > SERVO_ZERO_POSITION + 150) {
		_lights->traffRight(true);
	} else if (position < SERVO_ZERO_POSITION - 150) {
		_lights->traffLeft(true);
	} else {
		_lights->traffRight(false);
		_lights->traffLeft(false);
	}
}

void Steering::update() {
	if (CPPM.ok()) {
		errorCounter = 0;
		int16_t channelsValue = CPPM.readChannel(1);
		iCppmPosition = Steering::convertPosition(channelsValue);
	} else {
		++errorCounter;
		if (errorCounter > CPPM_MAX_ERRORS) {
			errorCounter = 0;
			iCppmPosition = SERVO_ZERO_POSITION;
			Serial.print("Comunication error!! Set center");
			Serial.print("\n");
		}
	}

	if ( abs(iCppmPositionLast - iCppmPosition) > DEADBAND
			&& errorCounter == 0) { //DEADBAND
		iCppmPositionLast = iCppmPosition;
		Serial.print("Set Servo Position: ");
		Serial.print(iCppmPosition);
		Serial.print("\n");

		sServo.write(iCppmPosition);
	}

	Steering::checkTrafficator(iCppmPosition);
}

void Steering::setup() {
	sServo.attach(3);
}
