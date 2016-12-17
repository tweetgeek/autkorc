#include "Trafficator.h"

Trafficator::Trafficator(uint8_t pin) {
	pinout = pin;
	isEnabled = false;
	ledState = false;
	previousMillis = 0;
	interval = 300;
}

void Trafficator::setup() {
	pinout = A0;
}

void Trafficator::update() {
	if (isEnabled) {
		unsigned long currentMillis = millis();

		if (currentMillis - previousMillis >= interval) {
			previousMillis = currentMillis;

			if (ledState == false) {
				ledState = true;
			} else {
				ledState = false;
			}

			analogWrite(pinout, ledState ? 255 : 0);
		}
	} else if (!isEnabled && ledState) {
		ledState = false;
		analogWrite(pinout, 0);
	}
}

void Trafficator::on() {
	if (!isEnabled) {
		Trafficator::off();
		isEnabled = true;
	}
}

void Trafficator::off() {
	if (isEnabled) {
		isEnabled = false;
		ledState = false;
		analogWrite(pinout, 0);
	}
}
