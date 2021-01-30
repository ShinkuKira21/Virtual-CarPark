/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

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
	// creates new carPark
	carPark = new CarPark();

	// initialises the objects spaces
	carPark->availableGeneralSpaces = gSpaces; 
	carPark->availableDisabilitySpaces = dSpaces;
	carPark->availableChildSpaces = cSpaces;
	
	// calculates the total spaces
	carPark->totalSpaces = carPark->availableGeneralSpaces + carPark->availableChildSpaces + carPark->availableDisabilitySpaces;

	//initialises the parking slot IDs
	InitialiseParkingSlotIDs();
}

CarPark::~CarPark()
{
	// cleans up pointers
	delete parkingSpaceID, parkingSpaceStatus;
}

// returns carPark sub obj
class CarPark* CarPark::GetClass() { return carPark; }

void CarPark::SetLocation(Vector& vec)
{
	carPark->SetVector(vec.GetVector(0), vec.GetVector(1), vec.GetVector(2));
}

Vector CarPark::GetLocation() { return Vector(GetVector(0),GetVector(1),GetVector(2)); }

std::string CarPark::AllocateParkingSpace(int parkingType)
{
	// calculates the max child spaces and max disabled spaces
	int maxChildSpace = carPark->availableGeneralSpaces + carPark->availableChildSpaces;
	int maxDisabledSpace = maxChildSpace + carPark->availableDisabilitySpaces;

	// Standard
	if (parkingType == 0)
	{
		// will find the first empty space of general space type
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
		// will find the first empty space of the child space
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
		// will find the first empty space of the disabled space
		for (int i = maxChildSpace; i < maxDisabledSpace; i++)
			if (carPark->parkingSpaceStatus[i] == "Empty")
			{
				carPark->parkingSpaceStatus[i] = "Taken";
				return carPark->parkingSpaceID[i];
			}
	}

	return "";
}


// deallocates parking spaces, for new cars to enter
bool CarPark::DeallocateParkingSpace(std::string argParkingSpaceID)
{
	for (int i = 0; i < carPark->totalSpaces; i++)
		if (argParkingSpaceID == carPark->parkingSpaceID[i])
		{
			if (carPark->parkingSpaceStatus[i] != "Empty")
			{
				carPark->parkingSpaceStatus[i] = "Empty";
				return true;
			}
			else
			{
				std::cout << ColorText("\nParking space already empty!", 37, 41) << std::endl;
				PauseSystem();
				return false;
			}
		}
		
	// if ID doesn't work
	std::cout << ColorText("\nCar park space does not exist!\n\n", 37, 41);
	PauseSystem();
	return false;
}

// Checkout: UT-CarPark solution.
// Inside will display how this logic was tested.
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

	// availableGeneralSpaces are full1
	if (carPark->availableGeneralSpaces - carPark->usedGeneralSpaces == 0) spaceCount -= 15; // if empty, add 1.
	if (carPark->availableDisabilitySpaces - carPark->usedDisabilitySpaces == 0) spaceCount += 2;
	if (carPark->availableChildSpaces - carPark->usedChildSpaces == 0) spaceCount -= 3;
	
	CountAvailableSpaces(); // count available spaces before change

	return spaceCount; // else turn true.
}

// Initialises the parkingSpaceIDs pointers
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

// counts the available spaces
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