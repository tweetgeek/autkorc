#include "DDD.h"
#include "Settings/Settings.h"
#include "CPPM/CPPM.h"
#include "Light/Light.h"
#include "Steering/Steering.h"
#include "Engine/Engine.h"

#define ddp Serial.print
#define ddpln Serial.println

void DDD::setup() {

}

void DDD::update() {

	unsigned long currentMillis = millis();
	if (currentMillis - this->previousMillis >= 1000) {
		this->previousMillis = currentMillis;
		ddpln("-----------------------------");
		ddp("{DDD} ");
		ddp("GEAR: ");
		switch (engine.getGear()) {
		case 0:
			ddp("1");
			break;
		case 1:
			ddp("2");
			break;
		case 2:
			ddp("3");
			break;
		case 3:
			ddp("R");
			break;
		}
		ddp(" \tSpeed: ");
		ddp(engine.getSpeed());
		ddp(" \tSteering: ");
		ddp(steering.getPosition());
		ddp(" \tLights: ");
		ddp(Lights.getStatus() ? "ON" : "OFF");
		ddp(" \tTraff: ");
		switch (Lights.getTraffStatus()) {
		case 0:
			ddp("OFF");
			break;
		case 1:
			ddp("LEFT");
			break;
		case 2:
			ddp("RIGHT");
			break;
		}
		ddpln("");

		ddp("{DDD CH} ");
		ddp("Thr: ");
		ddp(CPPM.readChannel(CPPM_THROTLE_CHANNEL));
		ddp(" \tAil: ");
		ddp(CPPM.readChannel(CPPM_STEERING_CHANNEL));
		ddp(" \tLight: ");
		ddp(CPPM.readChannel(CPPM_LIGHTS_CHANNEL));
		ddp(" \tGear: ");
		ddp(CPPM.readChannel(CPPM_GEAR_CHANNEL));
		ddp(" \tBack: ");
		ddp(CPPM.readChannel(CPPM_BACKGEAR_CHANNEL));
		ddp(" \t Horn: ");
		ddp(CPPM.readChannel(CPPM_HORN_CHANNEL));
		ddpln("");
	}
}
