#pragma once
#include "CardReader.h"

class Barrier : private CarPark
{
	protected:
		bool bBarrierStatus;

	public:
		Barrier(CarPark& carParkObj);
		~Barrier();

		void SetState(bool state);
		bool GetState();

		virtual void SetLocation(Vector& vec);
		virtual Vector GetLocation();
	private:
		void DisplayState();
};