#include "LIGHT.h"
#include "Arduino.h"
#include "Trafficator/Trafficator.h"
#include "CPPMHelper/CPPMHelper.h"

void Light::setup() {
	isEnabled = false;
	leftTraff.setup(A0);
	rightTraff.setup(A1);
}

void Light::update() {
	if (CPPM.ok()) {
		int16_t channelsValue = CPPM.readChannel(CPPM_LIGHTS_CHANNEL);

		if (RHelper.auxValue(channelsValue) == A_HIGH && !isEnabled) {
			isEnabled = true;
		} else if (RHelper.auxValue(channelsValue) == A_LOW && isEnabled) {
			isEnabled = false;
		}
	}

	analogWrite(A2, isEnabled ? 255 : 0);
	analogWrite(A3, isEnabled ? 255 : 0);

	leftTraff.update();
	rightTraff.update();
}

void Light::updateSteeringPosition(int16_t position) {
	if (position > SERVO_ZERO_POSITION + 150) {
		Light::traffRight(true);
	} else if (position < SERVO_ZERO_POSITION - 150) {
		Light::traffLeft(true);
	} else {
		Light::traffRight(false);
		Light::traffLeft(false);
	}
}

void Light::traffRight(bool status) {
	if (status) {
		rightTraff.on();
	} else {
		rightTraff.off();
	}
}
void Light::traffLeft(bool status) {
	if (status) {
		leftTraff.on();
	} else {
		leftTraff.off();
	}
}

