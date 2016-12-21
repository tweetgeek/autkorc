#include "HORN.h"
#include "Arduino.h"
#include "CPPM/CPPM.h"
#include "CPPMHelper/CPPMHelper.h"

void Horn::setup() {
}

void Horn::update() {
	int16_t channelsValue = 0;
	if (CPPM.ok()) {
		channelsValue = CPPM.readChannel(CPPM_HORN_CHANNEL);
	}

	if (RHelper.auxValue(channelsValue) > A_LOW) {
		Serial.println("TU UT UTUTUT");
		analogWrite(A5, 255);
	} else {
		analogWrite(A5, 0);
	}
}

Horn horn;

