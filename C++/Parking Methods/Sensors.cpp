/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "Sensors.h"

Sensor::Sensor(CarPark& carParkObj, float aTriggerWeight) : CarPark(carParkObj) 
{ triggerWeight = aTriggerWeight; }

Sensor::~Sensor() { }

void Sensor::SetLocation(Vector& vec) { SetVector(vec.GetVector(0), vec.GetVector(1), vec.GetVector(2)); }

Vector Sensor::GetLocation() { return Vector(GetVector(0), GetVector(1), GetVector(2)); }

// if carWeight >= triggerWeight then car is detected
void Sensor::ActivateTrigger(float carWeight)
{
	if (carWeight >= triggerWeight) bIsPressed = true;
	else bIsPressed = false;
}

// Returns the status of the sensor
bool Sensor::GetStatus() { return bIsPressed; }