#ifndef STEERING_H
#define STEERING_H

#include <Settings/Settings.h>
#include "Arduino.h"
#include "Light/Light.h"
#include "ServoTimer2/ServoTimer2.h"

class Steering {
private:
	int16_t iCppmPosition;
	int16_t iCppmPositionLast;
	int errorCounter;
	ServoTimer2 sServo;
	Light *_lights;

public:
	Steering(Light *lights);
	void update();
	void setup();
	int16_t convertPosition(int16_t currentValue);
	int16_t fixRange(int16_t value);
	void checkTrafficator(int16_t position);
};

#endif
