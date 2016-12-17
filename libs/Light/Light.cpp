#include "LIGHT.h"
#include "Arduino.h"
#include "Trafficator/Trafficator.h"
#include "CPPM/CPPM.h"
#include "CPPMHelper/CPPMHelper.h"

void Light::setup() {
	this->isEnabled = false;
	this->leftTraff.setup(A0);
	this->rightTraff.setup(A1);
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
	}

	analogWrite(A2, this->isEnabled ? 255 : 0);
	analogWrite(A3, this->isEnabled ? 255 : 0);

	leftTraff.update();
	this->rightTraff.update();
}

void Light::updateSteeringPosition(int16_t position) {
	if (position > SERVO_ZERO_POSITION + 150) {
		this->traffRight(true);
	} else if (position < SERVO_ZERO_POSITION - 150) {
		this->traffLeft(true);
	} else {
		this->traffRight(false);
		this->traffLeft(false);
	}
}

void Light::traffRight(bool status) {
	if (status) {
		this->rightTraff.on();
	} else {
		this->rightTraff.off();
	}
}
void Light::traffLeft(bool status) {
	if (status) {
		this->leftTraff.on();
	} else {
		this->leftTraff.off();
	}
}

