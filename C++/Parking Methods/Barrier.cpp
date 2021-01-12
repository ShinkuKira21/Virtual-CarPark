#include "Barrier.h"

Barrier::Barrier(CarPark& carParkObj, bool state) : CarPark(carParkObj)
{
	SetState(state);
}

Barrier::~Barrier() { }

void Barrier::SetState(bool state) { bBarrierStatus = state; }

void Barrier::DisplayState() 
{ 
	if (bBarrierStatus)
		std::cout << "Barrier is open!\n";
	else
		std::cout << "Barrier is closed!\n";
}