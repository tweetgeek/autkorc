//#include <TB6612FNG.h>

#include "Settings/Settings.h"
#include "CPPM/CPPM.h"
#include "Light/Light.h"
#include "Engine/Engine.h"
#include "Steering/Steering.h"
#include "DDD/DDD.h"

//PINOUT
// 3 - servo (2 zablokowana timer)
// 8 - cppm (9 10 zablokowane)

//Pierwszy Bieg
//Drugi Bieg
//Trzeci Bieg
//Wsteczny
//Światła włączone
//Światła wyłączone

//Light lights;
//Steering steering;
//Engine engine;
DDD ddd;

void setup(void) {
	Serial.begin(115200);
	CPPM.begin(CPPM_NUM_CHANNELS);
	Lights.setup();
	steering.setup();
	engine.setup();
	ddd.setup();
}

void loop(void) {
	steering.update();
	engine.update();
	Lights.update();
	ddd.update();
	delay(27);
}
