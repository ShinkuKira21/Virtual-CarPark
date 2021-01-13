#include "Sensors.h"

Sensor::Sensor(CarPark& carParkObj, float aTriggerWeight) : CarPark(carParkObj) 
{ triggerWeight = aTriggerWeight; }

Sensor::~Sensor() { }

void Sensor::SetLocation(Vector& vec) { }

void Sensor::ActivateTrigger(float carWeight)
{
	if (carWeight >= triggerWeight) bIsPressed = true;
	else bIsPressed = false;
}

bool Sensor::GetStatus() { return bIsPressed; }