#include "LIGHT.h"
#include "Arduino.h"
#include "Trafficator/Trafficator.h"
#include "CPPM/CPPM.h"
#include "CPPMHelper/CPPMHelper.h"

void Light::setup() {
	this->isEnabled = false;
	this->isBackGearEnabled = false;
	this->leftTraff.setup(LIGHTS_LEFT_PIN_OUT);
	this->rightTraff.setup(LIGHTS_RIGHT_PIN_OUT);
}

void Light::update() {
	if (CPPM.ok()) {
		int16_t channelsValue = CPPM.readChannel(CPPM_LIGHTS_CHANNEL);
		if (RHelper.auxValue(channelsValue) == A_HIGH && !this->isEnabled) {
			this->isEnabled = true;
		} else if (RHelper.auxValue(channelsValue) == A_LOW
				&& this->isEnabled) {
			this->isEnabled = false;
		}

		channelsValue = CPPM.readChannel(CPPM_BACKGEAR_CHANNEL);
		if (RHelper.auxValue(channelsValue) == A_HIGH
				&& !this->isBackGearEnabled) {
			this->isBackGearEnabled = true;
		} else if (RHelper.auxValue(channelsValue) == A_LOW
				&& this->isBackGearEnabled) {
			this->isBackGearEnabled = false;
		}
	}

	analogWrite(LIGHTS_MAIN_PIN_OUT, this->isEnabled ? 255 : 0);
	analogWrite(LIGHTS_REAR_PIN_OUT, this->isEnabled ? 255 : 0);
	analogWrite(LIGHTS_BACK_PIN_OUT, this->isBackGearEnabled ? 255 : 0);

	this->leftTraff.update();
	this->rightTraff.update();
}

void Light::updateSteeringPosition(int16_t position) {
	if (position > SERVO_ZERO_POSITION + 150) {
		this->traffRight(ON);
	} else if (position < SERVO_ZERO_POSITION - 150) {
		this->traffLeft(ON);
	} else {
		this->traffRight(OFF);
		this->traffLeft(OFF);
	}
}

void Light::traffRight(bool status) {
	if (status == ON) {
		this->rightTraff.on();
	} else {
		this->rightTraff.off();
	}
}
void Light::traffLeft(bool status) {
	if (status == ON) {
		this->leftTraff.on();
	} else {
		this->leftTraff.off();
	}
}

bool Light::getStatus() {
	return this->isEnabled;
}

int Light::getTraffStatus() {
	if (this->leftTraff.getStatus())
		return 1;
	if (this->rightTraff.getStatus())
		return 2;
	return 0;
}

Light Lights;

