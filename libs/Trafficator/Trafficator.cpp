#include "Trafficator.h"

void Trafficator::setup(uint8_t pin) {
	this->isEnabled = false;
	this->ledState = false;
	this->previousMillis = 0;
	this->interval = 300;
	this->pinout = pin;
}

void Trafficator::update() {
	if (this->isEnabled) {
		unsigned long currentMillis = millis();

		if (currentMillis - this->previousMillis >= this->interval) {
			this->previousMillis = currentMillis;

			if (this->ledState == false) {
				this->ledState = true;
			} else {
				this->ledState = false;
			}

			analogWrite(this->pinout, this->ledState ? 255 : 0);
		}
	} else if (!this->isEnabled && this->ledState) {
		this->ledState = false;
		analogWrite(this->pinout, 0);
	}
}

void Trafficator::on() {
	if (!this->isEnabled) {
		this->off();
		this->isEnabled = true;
	}
}

void Trafficator::off() {
	if (this->isEnabled) {
		this->isEnabled = false;
		this->ledState = false;
		analogWrite(this->pinout, 0);
	}
}

bool Trafficator::getStatus() {
	return this->isEnabled;
}
