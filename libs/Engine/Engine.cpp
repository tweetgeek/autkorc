#include "Engine/Engine.h"
#include "Light/Light.h"
#include "GearBox/GearBox.h"
#include "Arduino.h"
#include "CPPM/CPPM.h"
#include "CPPMHelper/CPPMHelper.h"

void Engine::setup() {
	this->gearBox.setup();

	pinMode(ENGINE_PIN_STBY, OUTPUT);
	pinMode(ENGINE_PIN_IN_1, OUTPUT);
	pinMode(ENGINE_PIN_IN_2, OUTPUT);
	pinMode(ENGINE_PIN_PWMA, OUTPUT);

	digitalWrite(ENGINE_PIN_STBY, 1);
	digitalWrite(ENGINE_PIN_IN_1, 0);
	digitalWrite(ENGINE_PIN_IN_2, 0);
	analogWrite(ENGINE_PIN_PWMA, 0);

	this->errorCounter = 0;
	this->iCppmPosition = 0;
	this->iCppmPositionLast = 0;
	this->isActive = false;
	this->isLocked = false;
}

void Engine::update() {
	this->gearBox.update();

	if (CPPM.ok()) {
		this->errorCounter = 0;
		int16_t channelsValue = CPPM.readChannel(CPPM_THROTLE_CHANNEL);
		if (abs(channelsValue - this->iCppmPosition) < 100) {
			this->iCppmPosition = channelsValue;
		}
	} else {
		++this->errorCounter;
		if (this->errorCounter > CPPM_MAX_ERRORS) {
			this->errorCounter = 0;
		}
	}

	if (this->isLocked) {
		this->hardBrake();
//		this->sleep();

		if (this->iCppmPosition == 0) {
			this->isLocked = false;
		}
	} else if (RHelper.deadbandFilter(this->iCppmPositionLast,
			this->iCppmPosition) && this->errorCounter == 0) { //DEADBAND

		if (this->iCppmPosition >= 10) {
			this->activate();
		} else if (this->iCppmPosition < 10) {
			this->sleep();
		}

		if (this->isActive) {
			this->drive();
		}

		if (this->iCppmPositionLast == 0 && this->iCppmPosition == 0) {
			this->brake();
		}
		this->iCppmPositionLast = this->iCppmPosition;
	}
}

void Engine::drive() {
	if (this->gearBox.is(A_HIGH)) {
		digitalWrite(ENGINE_PIN_IN_2, 0);
		digitalWrite(ENGINE_PIN_IN_1, 1);
	} else {
		digitalWrite(ENGINE_PIN_IN_1, 0);
		digitalWrite(ENGINE_PIN_IN_2, 1);
	}
	analogWrite(ENGINE_PIN_PWMA, this->getSpeed());
}

void Engine::brake() {
	digitalWrite(ENGINE_PIN_IN_1, 1);
	digitalWrite(ENGINE_PIN_IN_2, 1);
}

void Engine::hardBrake() {
	digitalWrite(ENGINE_PIN_IN_1, 0);
	digitalWrite(ENGINE_PIN_IN_2, 0);
}

void Engine::sleep() {
	if (this->isActive) {
		digitalWrite(ENGINE_PIN_STBY, 0);
		this->isActive = false;
	}
}

void Engine::activate() {
	if (this->isActive == false) {
		this->isActive = true;
		digitalWrite(ENGINE_PIN_STBY, 1);
	}
}

int16_t Engine::getSpeed() {
	if (this->gearBox.is(A_MEDIUM))
		return map(this->iCppmPosition, 0, 255, 0, 255);

	if (this->gearBox.is(A_HIGH)) //wsteczny
		return map(this->iCppmPosition, 0, 255, 0, 190);

	return map(this->iCppmPosition, 0, 255, 0, ENGINE_MAX_PWM);
}

int Engine::getGear() {
	return this->gearBox.get();
}

Engine engine;
