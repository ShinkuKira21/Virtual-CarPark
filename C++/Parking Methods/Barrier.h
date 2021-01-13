#pragma once
#include "CardReader.h"

class Barrier : private CarPark
{
	protected:
		bool bBarrierStatus;

	public:
		Barrier(CarPark& carParkObj);
		~Barrier();

		virtual void SetLocation(Vector& vec);

	private:
		void SetState(bool state);
		void DisplayState();
};

