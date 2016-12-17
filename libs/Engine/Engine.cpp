#include "Engine/Engine.h"
#include "Light/Light.h"
#include "Arduino.h"
#include "CPPM/CPPM.h"

void Engine::setup(Light& lightRef) {
	lights = lightRef;
}

int Engine::getSpeed() {
	if (!CPPM.ok())
		return -1;
	return CPPM.readChannel(0);
}

bool Engine::getDirection() {
	if (!CPPM.ok())
		return false;
	return CPPM.readChannel(2);
}

void Engine::update() {
	//  lights.frontOn();
}
