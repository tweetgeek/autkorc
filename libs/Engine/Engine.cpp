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
//			this->iCppmPosition = 0;
//			Serial.print("Comunication error!! Set zero");
//			Serial.print("\n");
		}
	}

	if (RHelper.deadbandFilter(this->iCppmPositionLast, this->iCppmPosition)
			&& this->errorCounter == 0) { //DEADBAND

//		Serial.print("Set thr ");
//		Serial.print(this->iCppmPosition);
//		Serial.print("\n");
		if (this->iCppmPosition >= 10) {
			this->activate();
		} else if (this->iCppmPosition < 10) {
			this->sleep();
		}

		if (this->isActive) {
			this->drive();
		}

		if (this->iCppmPositionLast > this->iCppmPosition) {
//			this->brake();
		}

		this->iCppmPositionLast = this->iCppmPosition;
	}
}

void Engine::drive() {
	digitalWrite(ENGINE_PIN_IN_1, 0);
	digitalWrite(ENGINE_PIN_IN_2, 1);
	analogWrite(ENGINE_PIN_PWMA, this->getSpeed());
//	Serial.print("Speed: ");
//	Serial.println(this->getSpeed());
}

void Engine::brake() {
	digitalWrite(ENGINE_PIN_IN_1, 1);
	digitalWrite(ENGINE_PIN_IN_2, 1);
}

void Engine::sleep() {
	if (this->isActive) {
		Serial.println("Sleep");
		digitalWrite(ENGINE_PIN_STBY, 0);
		this->isActive = false;
	}
}

void Engine::activate() {
	if (this->isActive == false) {
		Serial.println("Activate");
		this->isActive = true;
		digitalWrite(ENGINE_PIN_STBY, 1);
	}
}

int16_t Engine::getSpeed() {
	if (this->gearBox.is(A_MEDIUM))
		return map(this->iCppmPosition, 0, 255, 0, 128);
	if (this->gearBox.is(A_HIGH))
		return map(this->iCppmPosition, 0, 255, 0, ENGINE_MAX_PWM);

	return map(this->iCppmPosition, 0, 255, 0, 64);
}

int Engine::getGear() {

	return this->gearBox.get();
}

Engine engine;
