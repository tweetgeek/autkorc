#ifndef ENGINE_H
#define ENGINE_H

#include "Arduino.h"
#include "Light/Light.h"
#include "CPPM/CPPM.h"

class Engine {
private:
	Light _lights;
	int errorCounter;
	int gear;
	int16_t iCppmPosition;
	int16_t iCppmPositionLast;

public:
	void update();
	void setup(Light &lights);
};

#endif
