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
		case -15:
			return "All Spaces are Empty.";

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