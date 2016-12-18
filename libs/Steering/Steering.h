#ifndef STEERING_H
#define STEERING_H

#include <Settings/Settings.h>
#include "Arduino.h"
#include "ServoTimer2/ServoTimer2.h"

class Steering {
private:
	int16_t iCppmPosition;
	int16_t iCppmPositionLast;
	int errorCounter;
	ServoTimer2 sServo;

public:
	void update();
	void setup();
	int16_t convertPosition(int16_t currentValue);
	int16_t fixRange(int16_t value);
	int16_t getPosition();
};


extern Steering steering;

#endif
