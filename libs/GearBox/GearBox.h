#ifndef GEARBOX_H
#define GEARBOX_H

#include "Arduino.h"

class GearBox {
private:
	int gear;
	int oldGear;

public:
	void update();
	void setup();
	int get();
	bool is(int auxValue);
};

#endif
