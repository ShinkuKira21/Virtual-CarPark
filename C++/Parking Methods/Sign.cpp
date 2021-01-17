/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "Sign.h"

Sign::Sign(CarPark& carParkObj) : CarPark(carParkObj)
{
	DisplayText();
}

Sign::~Sign() { }

std::string Sign::GetParkStatusMessage(int parkingSpace, std::string parkingSpaceID)
{
	switch (GetAvailabilityStatus())
	{
		case -15:
			return "Available Spaces";

		case -30:
			return "General Spaces are Full.";

		case -28:
			return "General Spaces and Disability Spaces are Full.";

		case -13:
			return "Disability Spaces are full.";

		case -18:
			return "Child Spaces are Full.";

		case -33: 
			return "General Spaces and Child Spaces are Full";

		case -16:
			return "Disability and Child Spaces are Full";

		default:
			return "Error: Car Park is full.";
	}
}

void Sign::SetLocation(Vector& vec) { SetVector(vec.GetVector(0), vec.GetVector(1), vec.GetVector(2)); }

Vector Sign::GetLocation(){ return Vector(GetVector(0), GetVector(1), GetVector(2)); }

void Sign::DisplayText()
{
	std::cout << "\t\t\tCar Park | Message Board\n\n\t";
	std::cout << GetParkStatusMessage() << std::endl << std::endl << std::endl << std::endl;
}