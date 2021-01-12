#pragma once
#include "CardReader.h"

class Sensor : private CarPark
{
	protected:

	public:
		Sensor(CarPark& carParkObj);
		~Sensor();

		virtual void SetLocation(Vector& vec);

	private:

};
