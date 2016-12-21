#ifndef HORN_H
#define HORN_H

#include "Arduino.h"

class Horn {

public:
	void update();
	void setup();
};

extern Horn horn;

#endif
