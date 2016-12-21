#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"
#include "Trafficator/Trafficator.h"

class Light {
private:
	bool isEnabled;
	bool isBackGearEnabled;
	Trafficator leftTraff;
	Trafficator rightTraff;

public:
	void update();
	void setup();
	void updateSteeringPosition(int16_t position);
	void updateGearPosition(int position);
	void traffRight(bool status);
	void traffLeft(bool status);
	bool getStatus();
	int getTraffStatus();
};

extern Light Lights;

#endif
