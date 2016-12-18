#include "Steering.h"
#include "Arduino.h"
#include "CPPM/CPPM.h"
#include "Light/Light.h"
#include "CPPMHelper/CPPMHelper.h"
#include "ServoTimer2/ServoTimer2.h"

int16_t Steering::convertPosition(int16_t currentValue) {
	if (currentValue) {
		return this->fixRange(map(currentValue, 0, 255, SERVO_MAX_ANGLE_LEFT,
		SERVO_MAX_ANGLE_RIGHT));
	}
	return 0;
}

int16_t Steering::fixRange(int16_t value) {
	if (value == 0)
		return this->iCppmPositionLast;
	if (value < SERVO_MAX_ANGLE_LEFT)
		return SERVO_MAX_ANGLE_LEFT;
	if (value > SERVO_MAX_ANGLE_RIGHT)
		return SERVO_MAX_ANGLE_RIGHT;
	return value;
}

void Steering::update() {
	if (CPPM.ok()) {
		this->errorCounter = 0;
		int16_t channelsValue = CPPM.readChannel(CPPM_STEERING_CHANNEL);
		this->iCppmPosition = Steering::convertPosition(channelsValue);
	} else {
		++this->errorCounter;
		if (this->errorCounter > CPPM_MAX_ERRORS) {
			this->errorCounter = 0;
			this->iCppmPosition = SERVO_ZERO_POSITION;
//			Serial.print("Comunication error!! Set center");
//			Serial.print("\n");
		}
	}

	if (RHelper.deadbandFilter(this->iCppmPositionLast, this->iCppmPosition)
			&& this->errorCounter == 0) { //DEADBAND
		this->iCppmPositionLast = this->iCppmPosition;
//		Serial.print("Set Servo Position: ");
//		Serial.print(this->iCppmPosition);
//		Serial.print("\n");

		this->sServo.write(this->iCppmPosition);
	}

	Lights.updateSteeringPosition(this->iCppmPosition);
}

void Steering::setup() {
	this->iCppmPosition = SERVO_ZERO_POSITION;
	this->iCppmPositionLast = SERVO_ZERO_POSITION;
	this->errorCounter = 0;

	this->sServo.attach(3);
}

int16_t Steering::getPosition() {
	return this->iCppmPosition;
}

Steering steering;
