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
	void update();
	void setup(uint8_t pin);
	void on();
	void off();
};

#endif
