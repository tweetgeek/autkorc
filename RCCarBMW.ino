//#include <TB6612FNG.h>

#include "Settings/Settings.h";

#include "Light/Light.h"
#include "Engine/Engine.h"
#include "Steering/Steering.h"


//PINOUT
// 3 - servo (2 zablokowana timer)
// 8 - cppm (9 10 zablokowane)

Steering steering = Steering();
Engine engine = Engine();


void setup(void)
{
        Serial.begin(9600);
        CPPM.begin(CPPM_NUM_CHANNELS);
        steering.setup();
//        engine.setup();
}

void loop(void)
{
        steering.update();
        engine.update();
        // delay(27);
}
