#ifndef TRAFFICATOR_H
#define TRAFFICATOR_H

#include <Settings/Settings.h>
#include "Arduino.h"

class Trafficator
{
private:
        int pinout;
        bool isEnabled;
        int ledState;
        long previousMillis;
        long interval;

public:
        Trafficator(int pin);
        void update();
        void setup();
        void on();
        void off();
};

#endif
