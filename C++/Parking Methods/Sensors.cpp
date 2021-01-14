#include "Sensors.h"

Sensor::Sensor(CarPark& carParkObj, float aTriggerWeight) : CarPark(carParkObj) 
{ triggerWeight = aTriggerWeight; }

Sensor::~Sensor() { }

void Sensor::SetLocation(Vector& vec) { SetVector(vec.GetVector(0), vec.GetVector(1), vec.GetVector(2)); }

Vector Sensor::GetLocation() { return Vector(GetVector(0), GetVector(1), GetVector(2)); }

void Sensor::ActivateTrigger(float carWeight)
{
	if (carWeight >= triggerWeight) bIsPressed = true;
	else bIsPressed = false;
}

bool Sensor::GetStatus() { return bIsPressed; }