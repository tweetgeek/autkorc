//#include <TB6612FNG.h>

#include "Settings/Settings.h"
#include "CPPM/CPPM.h"
#include "Light/Light.h"
#include "Engine/Engine.h"
#include "Steering/Steering.h"

//PINOUT
// 3 - servo (2 zablokowana timer)
// 8 - cppm (9 10 zablokowane)

//Pierwszy Bieg
//Drugi Bieg
//Trzeci Bieg
//Wsteczny
//Światła włączone
//Światła wyłączone

Light lights;
Steering steering;
Engine engine;

void setup(void) {
	Serial.begin(9600);
	CPPM.begin(CPPM_NUM_CHANNELS);
	lights.setup();
	steering.setup(lights);
	engine.setup(lights);
}

void loop(void) {
	steering.update();
	engine.update();
	lights.update();
}
