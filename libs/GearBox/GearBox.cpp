#include "GearBox/GearBox.h"
#include "Arduino.h"
#include "CPPM/CPPM.h"
#include "CPPMHelper/CPPMHelper.h"
#include "Light/Light.h"
#include "Engine/Engine.h"

void GearBox::setup() {
	this->gear = A_LOW;
	this->oldGear = A_LOW;
}

void GearBox::update() {
	if (CPPM.ok()) {
		int16_t channelsValue = CPPM.readChannel(CPPM_GEAR_CHANNEL);
		this->gear = RHelper.auxValue(channelsValue);
	} else {
		this->gear = A_LOW;
	}

	Lights.updateGearPosition(this->gear);

	if ((this->oldGear != A_HIGH && this->gear == A_HIGH)
			|| (this->oldGear == A_HIGH && this->gear != A_HIGH)) {
		engine.isLocked = true;
		Serial.println("LOCKED!");
	}

	this->oldGear = this->gear;
}

int GearBox::get() {
	return this->gear;
}

bool GearBox::is(int auxValue) {
	return this->get() == auxValue;
}
