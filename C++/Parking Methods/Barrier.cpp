/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "Barrier.h"

Barrier::Barrier(CarPark& carParkObj) : CarPark(carParkObj) { SetState(false); }

Barrier::~Barrier() { }

void Barrier::SetLocation(Vector& vec) { SetVector(vec.GetVector(0), vec.GetVector(1), vec.GetVector(2)); }

Vector Barrier::GetLocation() { return Vector(GetVector(0), GetVector(1), GetVector(2)); }

void Barrier::SetState(bool state) { bBarrierStatus = state; }

bool Barrier::GetState() { return bBarrierStatus; }

void Barrier::DisplayState() 
{ 
	if (bBarrierStatus)
		std::cout << "Barrier is open!\n";
	else
		std::cout << "Barrier is closed!\n";
}