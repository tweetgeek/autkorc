#ifndef LIGHT_H
#define LIGHT_H

#include "Arduino.h"

class Light
{
private:
        int isa;
        uint8_t frontPin;
        uint8_t rearPin;
        uint8_t breakPin;

        bool frontEnabled = false;
        bool rearEnabled = false;
        bool breakEnabled = false;

public:
        Light();
        void update();
        void setup();
        void frontOn();
        void frontOff();
        void rearOn();
        void rearOff();
        void breakOn();
        void breakOff();
};

#endif
