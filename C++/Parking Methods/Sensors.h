/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#pragma once
#include "CardReader.h"

class Sensor : private CarPark
{
	protected:
		bool bIsPressed; float triggerWeight;

	public:
		Sensor(CarPark& carParkObj, float aTriggerWeight);
		~Sensor();

		bool GetStatus();
		void ActivateTrigger(float carWeight);

		virtual void SetLocation(Vector& vec);
		virtual Vector GetLocation();
};