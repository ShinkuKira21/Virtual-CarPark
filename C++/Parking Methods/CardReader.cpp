/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "CardReader.h"

// Card Memberships
CardReader::CardReader(CarPark& carParkObj, int mode, std::string membershipID, std::vector<Card>* card) : CarPark(carParkObj)
{
	// sets up barrier and sensors
	BarrierSetup(carParkObj);
	SensorSetup(carParkObj);

	// Sets CardReader::SetLocation virtual class
	this->SetLocation(*new Vector(2.4f, 20.5, -20.f)); // shown different ways to call a virtual

	// determines whether to add/remove vehicle
	if (mode == 1) VehicleIncrement(membershipID, card);
	if (mode == 0) VehicleDecrement();

	if (mode != 2)
		ClearSystem();
}

CardReader::~CardReader() { }

Vector CardReader::GetSubclassLocation(int mode)
{
	/* 0 will return CardReader's location
	*  1 will return entranceBarrier's location
	*  2 will return exitBarrier's location
	*  3 will return entranceSensor's location
	*  4 will return exit Sensor's location
	*  5 will return blank Vector object if an error occured.
	*/
	if (mode == 0) return GetLocation();
	if (mode == 1) return entranceBarrier->GetLocation();
	if (mode == 2) return exitBarrier->GetLocation();
	if (mode == 3) return entranceSensor->GetLocation();
	if (mode == 4) return exitSensor->GetLocation();
	
	return Vector();
}

void CardReader::BarrierSetup(CarPark& carParkObj)
{
	// initialises new barrier to both entrance and exit barriers.
	entranceBarrier = new Barrier(carParkObj);
	exitBarrier = new Barrier(carParkObj);

	// set's location to both entrance and exit barrier's
	entranceBarrier->SetLocation(*new Vector(1.20f, 1.15f, 2.f));
	exitBarrier->SetLocation(*new Vector(20.f, 20.15f, 2.f));
}

void CardReader::SensorSetup(CarPark& carParkObj)
{
	// initialises new barrier to both entrance and exit sensor's
	entranceSensor = new Sensor(carParkObj, 1.5f);
	exitSensor = new Sensor(carParkObj, 1.5f);

	// set's location to both entrance and exit sensor's
	entranceSensor->SetLocation(*new Vector(1.10f, 1.05f, 1.5f));
	exitSensor->SetLocation(*new Vector(19.90f, 20.05f, 1.5f));
}

void CardReader::ActivateSensor(float vehicleWeight, bool inOut)
{
	// if inOut is true then call entrance sensor class
	if (inOut) entranceSensor->ActivateTrigger(vehicleWeight);
	else exitSensor->ActivateTrigger(vehicleWeight);
}

//add car to car park
void CardReader::VehicleIncrement(std::string membershipID, std::vector<Card>* card)
{
	// Entrance sensor
	ActivateSensor((float)NumberInput("Enter car weight (Tonnes): "), true);
	ClearSystem();

	// if car doesn't reaches weight minimum, then
	if (!entranceSensor->GetStatus())
	{
		// display on card reader that no car detected,
		// but you can still override system (incase sensor plays up)
		std::cout << "\t\t\tUser Interaction Menu\n\n";
		std::cout << "No car detected | Override Allowed\n\n";

		PauseSystem();
		ClearSystem();
	}
	
	// even if payment or parking failed, the car has to go around to get out

	bool pParkingStatus = UserInterface(membershipID, card);

	entranceBarrier->SetState(true); // opens entrance barrier
	if (entranceBarrier->GetState()) std::cout << "\nEntrance Barrier Open: Please drive through!\n";

	PauseSystem();
	ClearSystem();

	entranceBarrier->SetState(false); // closes entrance barrier
	if (!entranceBarrier->GetState()) std::cout << "Entrance Barrier Closed\n";

	PauseSystem();
	ClearSystem();

	// the user interface function is called
	// if payment method fails, 
	// then exit barriers will open and close.
	if (!pParkingStatus)
		VehicleDecrement(-1);
}

//remove car from car park
void CardReader::VehicleDecrement(int mode)
{
	// if default mode is detected ( two modes exit as the exit barriers, could open to let cars that needed to leave )
	if (mode == 0)
	{
		// display spaces, and asks (system), which space is empty
		DisplaySpaces();
		DeallocateParkingSpace(TextInput("Enter Parking Space ID: "));
	}

	ClearSystem();

	// opens and closes parking space
	exitBarrier->SetState(true);
	if (exitBarrier->GetState()) std::cout << "Exit Barrier Open: Please drive through!\n";

	PauseSystem();
	ClearSystem();

	entranceBarrier->SetState(false); // closes entrance barrier
	if (!entranceBarrier->GetState()) std::cout << "Exit Barrier Closed\n";

	PauseSystem();
}

// Enables set location of this class
void CardReader::SetLocation(Vector& vec) { SetVector(vec.GetVector(0), vec.GetVector(1), vec.GetVector(2)); }

//enables get location of this class
Vector CardReader::GetLocation() { return Vector(GetVector(0), GetVector(1), GetVector(2)); }

std::string CardReader::GetParkStatusMessage(int parkingSpace, std::string parkingSpaceID)
{
	int availabilityStatus = GetAvailabilityStatus();

	// only continue if car park is not full
	if (availabilityStatus != -31)
	{
		// combines Proceed to "Parking Space ID"
		if (parkingSpace == 0 && availabilityStatus != -30) return "Proceed to " + parkingSpaceID;
		if (parkingSpace == 1 && availabilityStatus != -18) return "Proceed to " + parkingSpaceID;
		if (parkingSpace == 2 && availabilityStatus != -13) return "Proceed to " + parkingSpaceID;
	}
		
	return "Please exit the car park."; // could send them back to the selection.

	DisplaySpaces();
}

// Checks User Card || Choose Parking Method
bool CardReader::UserInterface(std::string membershipID, std::vector<Card>* card)
{
	bool bParkingStatus = false;

	bParkingStatus = CheckMembershipCard(membershipID, card);

	// if bParkingStatus is true then ask user about their parking method
	if (bParkingStatus)
		bParkingStatus = ParkingMethod(); // if error message doesnt exist ask for parking method

	// else display error message
	else std::cout << ColorText("Invalid Card", 37, 41) << "\nPlease exit the carpark!" << std::endl;

	return bParkingStatus;
}

bool CardReader::CheckMembershipCard(std::string membershipID, std::vector<Card>* card)
{
	// Loop through user cards and if membershipID matches then return true.
	// date needs to change to integer to compare.
	for (int i = 0; i < card->size(); i++)
		if (card->at(i).membershipID == membershipID)
		{
			// If membershipType is visitor
			if ((card->at(i).membershipType == "V" || card->at(i).membershipType == "v"))
			{
				//If current date is equal to expiry date
				if (card->at(i).expiryDate == GetCurrentDate()) return true;
				// return false if vistor membership expired
				return false;
			}

			// if staff return true
			return true;
		}
		

	return false;
}

// Asks the user if they require special requirements
// Also, determines if there is any spaces available
bool CardReader::ParkingMethod()
{
	DisplaySpaces();

	int menu;
	menu = (int)NumberInput("\t\t\tUser Interaction Menu\n\nAny Special Places Required n(0/1)y: ");

	if (menu == 1) menu = (int)NumberInput("\nSelect Type: 1) Child | 2) Disabled: ");
	else menu = 0;

	std::string parkStatusMessage = GetParkStatusMessage(menu, AllocateParkingSpace(menu));

	std::cout << parkStatusMessage << std::endl;

	if (parkStatusMessage == "Please exit the car park.")
		return false; // parking failed.
	
	return true; //parking completed.
}

std::string CardReader::GetCurrentDate()
{
	// gets current time stamp
	time_t t = time(0);

	// gets local time based on machine configuration
	tm* localTime = new tm(); localtime_s(localTime, &t);

	// creates a date string "31/12/2000"
	return std::to_string(localTime->tm_mday) + "/" + std::to_string(1 + localTime->tm_mon) + "/" + std::to_string(1900 + localTime->tm_year);
}