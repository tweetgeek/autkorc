#ifndef CPPMHELPER_H
#define CPPMHELPER_H

#include "Arduino.h"
#include "Settings/Settings.h"

#define A_LOW 0
#define A_MEDIUM 1
#define A_HIGH 2

class CPPMHelper {
public:
	int deadbandFilter(int16_t lastPos, int16_t newPos) {
		return abs(lastPos - newPos) > DEADBAND;
	}

	int auxValue(int16_t value) {
		if (value > CPPM_POSITION_MEDIUM - CPPM_POSITION_RANGE
				&& value < CPPM_POSITION_MEDIUM + CPPM_POSITION_RANGE)
			return A_MEDIUM;
		if (value > CPPM_POSITION_HIGH - CPPM_POSITION_RANGE
				&& value < CPPM_POSITION_HIGH + CPPM_POSITION_RANGE)
			return A_HIGH;
		return A_LOW;
	}
};

extern CPPMHelper RHelper;

#endif
