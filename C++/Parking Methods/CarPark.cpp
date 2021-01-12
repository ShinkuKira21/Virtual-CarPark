#include "CarPark.h"

// Default Constructor
CarPark::CarPark() { }

CarPark::CarPark(CarPark& cPark) 
{
	// copy existing obj to current obj
	carPark = &cPark;
}

CarPark::CarPark(int gSpaces, int dSpaces, int cSpaces)
{
	carPark = new CarPark();

	carPark->availableGeneralSpaces = gSpaces; 
	carPark->availableDisabilitySpaces = dSpaces;
	carPark->availableChildSpaces = cSpaces;
	
	carPark->totalSpaces = carPark->availableGeneralSpaces + carPark->availableChildSpaces + carPark->availableDisabilitySpaces;

	InitialiseParkingSlotIDs();
}

CarPark::~CarPark()
{
	delete parkingSpaceID, parkingSpaceStatus;
}

// returns carPark sub obj
class CarPark* CarPark::GetClass() { return carPark; }

std::string CarPark::AllocateParkingSpace(int parkingType)
{
	int maxChildSpace = carPark->availableGeneralSpaces + carPark->availableChildSpaces;
	int maxDisabledSpace = maxChildSpace + carPark->availableDisabilitySpaces;

	// Standard
	if (parkingType == 0)
	{
		for (int i = 0; i < carPark->availableGeneralSpaces; i++)
			if (carPark->parkingSpaceStatus[i] == "Empty")
			{
				carPark->parkingSpaceStatus[i] = "Taken";
				return carPark->parkingSpaceID[i];
			}
	}
				
	// Child
	else if (parkingType == 1)
	{
		for (int i = carPark->availableGeneralSpaces; i < maxChildSpace; i++)
			if (carPark->parkingSpaceStatus[i] == "Empty")
			{
				carPark->parkingSpaceStatus[i] = "Taken";
				return carPark->parkingSpaceID[i];
			}
	}
					

	// Disabled
	else
	{
		for (int i = maxChildSpace; i < maxDisabledSpace; i++)
			if (carPark->parkingSpaceStatus[i] == "Empty")
			{
				carPark->parkingSpaceStatus[i] = "Taken";
				return carPark->parkingSpaceID[i];
			}
	}

	return "";
}

void CarPark::DeallocateParkingSpace(std::string argParkingSpaceID)
{
	// Double Check !! IMPORTANT !!
	for (int i = 0; i < carPark->totalSpaces; i++)
		if (argParkingSpaceID == carPark->parkingSpaceID[i])
		{
			if (carPark->parkingSpaceStatus[i] != "Empty") carPark->parkingSpaceStatus[i] = "Empty";
			else std::cout << "Parking space already empty!" << std::endl;
		}
}

int CarPark::GetAvailabilityStatus()
{
	/* Code Identifiers and Meanings:
	* Number: -15 - All Spaces are Empty
	* Number: -30 - General Spaces are Full
	* Number: -28 - General Spaces and Disability Spaces are Full
	* Number: -13 - Disability Spaces are Full
	* Number: -31 - All Spaces are Full
	* Number: -18 - Child Spaces are Full
	* Number: -33 - General Spaces and Child Spaces are Full
	* Number: -16 - Disability and Child Spaces are Full
	*/

	// smarter to suggest which spaces are full
	int spaceCount = -15;

	// availableGeneralSpaces are full
	if (carPark->availableGeneralSpaces - carPark->usedGeneralSpaces == 0) spaceCount -= 15; // if empty, add 1.
	if (carPark->availableDisabilitySpaces - carPark->usedDisabilitySpaces == 0) spaceCount += 2;
	if (carPark->availableChildSpaces - carPark->usedChildSpaces == 0) spaceCount -= 3;

	return spaceCount; // else turn true.
}

std::string CarPark::GetParkingSpaceNumber() { return nullptr; }

void CarPark::InitialiseParkingSlotIDs()
{
	carPark->parkingSpaceID = new std::string[carPark->totalSpaces];
	carPark->parkingSpaceStatus = new std::string[carPark->totalSpaces];

	int maxChildSpace = carPark->availableGeneralSpaces + carPark->availableChildSpaces;
	int maxDisabledSpace = maxChildSpace + carPark->availableDisabilitySpaces;

	for (int i = 0; i < carPark->availableGeneralSpaces; i++)
	{
		carPark->parkingSpaceID[i] = parkingSpaceIDs[0] + std::to_string(i);
		carPark->parkingSpaceStatus[i] = "Empty";
	}
		

	for (int i = carPark->availableGeneralSpaces; i < maxChildSpace; i++)
	{
		carPark->parkingSpaceID[i] = parkingSpaceIDs[1] + std::to_string(i);
		carPark->parkingSpaceStatus[i] = "Empty";
	}
		

	for (int i = maxChildSpace; i < maxDisabledSpace; i++)
	{
		carPark->parkingSpaceID[i] = parkingSpaceIDs[2] + std::to_string(i);
		carPark->parkingSpaceStatus[i] = "Empty";
	}
}

void CarPark::CountAvailableSpaces()
{
	int maxChildSpace = carPark->availableGeneralSpaces + carPark->availableChildSpaces;
	int maxDisabledSpace = maxChildSpace + carPark->availableDisabilitySpaces;

	carPark->usedGeneralSpaces = carPark->usedChildSpaces = carPark->usedDisabilitySpaces = 0;

	for (int i = 0; i < carPark->availableGeneralSpaces; i++)
		if (carPark->parkingSpaceStatus[i] == "Taken")
			carPark->usedGeneralSpaces++;

	for (int i = carPark->availableGeneralSpaces; i < maxChildSpace; i++)
		if (carPark->parkingSpaceStatus[i] == "Taken")
			carPark->usedChildSpaces++;

	for (int i = maxChildSpace; i < maxDisabledSpace; i++)
		if (carPark->parkingSpaceStatus[i] == "Taken")
			carPark->usedDisabilitySpaces++;
}