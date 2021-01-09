#include "Sign.h"

Sign::Sign(CarPark& carParkObj) : CarPark(carParkObj)
{
	
}

Sign::~Sign()
{

}

std::string Sign::GetParkStatusMessage(int parkingSpace, std::string parkingSpaceID)
{
	switch (GetAvailabilityStatus())
	{
		case -1:
			return "All Spaces are Empty.";

		case 0:
			return "General Spaces are Full.";

		case -3:
			return "General Spaces and Disability Spaces are Full.";

		case 3:
			return "Disability Spaces are full.";

		case 1:
			return "Child Spaces are Full.";

		case -4: 
			return "General Spaces and Child Spaces are Full";

		case 4:
			return "Disability and Child Spaces are Full";

		default:
			return "Error: Car Park is full.";
	}
}