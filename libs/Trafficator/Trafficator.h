#ifndef TRAFFICATOR_H
#define TRAFFICATOR_H

#include <Settings/Settings.h>
#include "Arduino.h"

class Trafficator {
private:
	uint8_t pinout;
	bool isEnabled;
	int ledState;
	long previousMillis;
	long interval;

public:
	Trafficator(uint8_t pin);
	void update();
	void setup();
	void on();
	void off();
};

#endif
