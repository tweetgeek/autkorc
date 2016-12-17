#ifndef ENGINE_H
#define ENGINE_H

#include "Arduino.h"
#include "Light/Light.h"
#include "CPPM/CPPM.h"

class Engine
{
private:
        uint8_t pwmPin;
        Light& lights;


public:
        Engine();
        void update();
        void setup(Light& lightRef);
        int getSpeed();
        bool getDirection();
};

#endif
