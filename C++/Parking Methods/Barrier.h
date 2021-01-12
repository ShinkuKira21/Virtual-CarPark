#pragma once
#include "CardReader.h"

class Barrier : private CarPark
{
	protected:
		bool bBarrierStatus;

	public:
		Barrier(CarPark& carParkObj);
		~Barrier();

	private:
		void SetState(bool state);
		void DisplayState();
};

