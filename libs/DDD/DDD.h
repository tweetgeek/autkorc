#ifndef DDD_H
#define DDD_H

#include "Arduino.h"

class DDD {
private:
	int errorCounter;
	long previousMillis;

public:
	void update();
	void setup();
};

#endif
