#include "LIGHT.h"
#include "Arduino.h"
#include "Trafficator/Trafficator.h"

Light::Light() {
	Trafficator leftTraff = Trafficator(A0);
	Trafficator rightTraff = Trafficator(A1);
}

void Light::setup() {
	leftTraff.setup();
	rightTraff.setup();
}

void Light::update() {
	leftTraff.update();
	rightTraff.update();
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

