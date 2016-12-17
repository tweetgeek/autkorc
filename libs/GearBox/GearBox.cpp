#include "GearBox/GearBox.h"
#include "Arduino.h"
#include "CPPM/CPPM.h"
#include "CPPMHelper/CPPMHelper.h"
//TODO FAILSAFE && DEADBAND
void GearBox::setup() {
	this->gear = A_LOW;
}

void GearBox::update() {
	if (CPPM.ok()) {
		int16_t channelsValue = CPPM.readChannel(CPPM_GEAR_CHANNEL);
		this->gear = RHelper.auxValue(channelsValue);
	} else {
		this->gear = A_LOW;
	}
}

int GearBox::get() {
	return this->gear;
}

bool GearBox::is(int auxValue) {
	return this->get() == auxValue;
}
