#include "Barrier.h"

Barrier::Barrier(CarPark& carParkObj) : CarPark(carParkObj) { SetState(false); }

Barrier::~Barrier() { }

void Barrier::SetLocation(Vector& vec) {}

void Barrier::SetState(bool state) { bBarrierStatus = state; }

bool Barrier::GetState() { return bBarrierStatus; }

void Barrier::DisplayState() 
{ 
	if (bBarrierStatus)
		std::cout << "Barrier is open!\n";
	else
		std::cout << "Barrier is closed!\n";
}