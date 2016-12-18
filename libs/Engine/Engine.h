#ifndef ENGINE_H
#define ENGINE_H

#include "Arduino.h"
#include "Light/Light.h"
#include "GearBox/GearBox.h"
#include "CPPM/CPPM.h"

class Engine {
private:
	int errorCounter;
	GearBox gearBox;
	int16_t iCppmPosition;
	int16_t iCppmPositionLast;
	bool isActive;

public:
	void update();
	void setup();
	void drive();
	void brake();
	int16_t getSpeed();
	void sleep();
	void activate();
	int getGear();
};


extern Engine engine;

#endif
