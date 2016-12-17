#include "Steering.h"
#include "Arduino.h"
#include "CPPM/CPPM.h"
#include "CPPMHelper/CPPMHelper.h"
#include "ServoTimer2/ServoTimer2.h"

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

void Steering::update() {
	if (CPPM.ok()) {
		errorCounter = 0;
		int16_t channelsValue = CPPM.readChannel(CPPM_STEERING_CHANNEL);
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

	if (RHelper.deadbandFilter(iCppmPositionLast, iCppmPosition)
			&& errorCounter == 0) { //DEADBAND
		iCppmPositionLast = iCppmPosition;
		Serial.print("Set Servo Position: ");
		Serial.print(iCppmPosition);
		Serial.print("\n");

		sServo.write(iCppmPosition);
	}

	_lights.updateSteeringPosition(iCppmPosition);
}

void Steering::setup(Light &lights) {
	iCppmPosition = SERVO_ZERO_POSITION;
	iCppmPositionLast = SERVO_ZERO_POSITION;
	errorCounter = 0;

	_lights = lights;
	sServo.attach(3);
}
