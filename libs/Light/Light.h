#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"
#include "Trafficator/Trafficator.h"

class Light {
private:
	Trafficator leftTraff;
	Trafficator rightTraff;

public:
	Light();
	void update();
	void setup();
	void traffRight(bool status);
	void traffLeft(bool status);
};

#endif
