#include "LIGHT.h"
#include "Arduino.h"

Light::Light () {
}

void Light::setup() {
        pinMode(frontPin, OUTPUT);
        pinMode(rearPin, OUTPUT);
        pinMode(breakPin, OUTPUT);

        digitalWrite(frontPin, LOW);
        digitalWrite(rearPin, LOW);
        digitalWrite(rearPin, LOW);
}

void Light::update() {
        digitalWrite(frontPin, frontEnabled ? HIGH : LOW);
        digitalWrite(rearPin, rearEnabled ? HIGH : LOW);
        digitalWrite(breakPin, breakEnabled ? HIGH : LOW);
}

void Light::frontOn() {
        frontEnabled = true;
}
void Light::frontOff() {
        frontEnabled = false;
}

void Light::rearOn() {
        frontEnabled = true;
}
void Light::rearOff() {
        rearEnabled = false;
}

void Light::breakOn() {
        breakEnabled = true;
}
void Light::breakOff() {
        breakEnabled = false;
}
