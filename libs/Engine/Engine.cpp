#include "Engine/Engine.h"
#include "Light/Light.h"
#include "GearBox/GearBox.h"
#include "Arduino.h"
#include "CPPM/CPPM.h"
#include "CPPMHelper/CPPMHelper.h"

void Engine::setup(Light& lights) {
	this->gearBox.setup();

	this->_lights = lights;

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
}

void Engine::update() {
	this->gearBox.update();

	if (CPPM.ok()) {
		this->errorCounter = 0;
		int16_t channelsValue = CPPM.readChannel(CPPM_THROTLE_CHANNEL);
		this->iCppmPosition = channelsValue;
	} else {
		++this->errorCounter;
		if (this->errorCounter > CPPM_MAX_ERRORS) {
			this->errorCounter = 0;
			this->iCppmPosition = 0;
			Serial.print("Comunication error!! Set zero");
			Serial.print("\n");
		}
	}

	if (RHelper.deadbandFilter(this->iCppmPositionLast, this->iCppmPosition)
			&& this->errorCounter == 0) { //DEADBAND

		if (this->iCppmPosition > 0
				&& this->iCppmPosition > this->iCppmPositionLast) {
			this->activate();
		} else {
			this->sleep();
		}

		if (this->isActive) {
			this->drive();
		}

		if (this->iCppmPositionLast > this->iCppmPosition) {
			this->brake();
		}

		this->iCppmPositionLast = this->iCppmPosition;
	}
}

void Engine::drive() {
	digitalWrite(ENGINE_PIN_IN_1, 0);
	digitalWrite(ENGINE_PIN_IN_2, 1);
	analogWrite(ENGINE_PIN_PWMA, this->getSpeed());
}

void Engine::brake() {
	digitalWrite(ENGINE_PIN_IN_1, 1);
	digitalWrite(ENGINE_PIN_IN_2, 1);
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
		return map(this->iCppmPosition, 0, 128, 0, 255);
	if (this->gearBox.is(A_HIGH))
		return map(this->iCppmPosition, 0, 255, 0, 255);

	return map(this->iCppmPosition, 0, 64, 0, 255);;
}
