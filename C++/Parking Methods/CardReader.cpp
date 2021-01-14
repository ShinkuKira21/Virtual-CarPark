#include "CardReader.h"

// Card Memberships
CardReader::CardReader(CarPark& carParkObj, int mode, std::string membershipID, std::vector<Card>* card) : CarPark(carParkObj)
{
	BarrierSetup(carParkObj);
	SensorSetup(carParkObj);

	// Sets CardReader::SetLocation virtual class
	this->SetLocation(*new Vector(2.4f, 20.5, -20.f)); // shown different ways to call a virtual

	if (mode == 1) VehicleIncrement(membershipID, card);
	if (mode == 0) VehicleDecrement();

	if (mode != 2)
	{
		PauseSystem();
		ClearSystem();
	}
}

CardReader::~CardReader() { }

Vector CardReader::GetSubclassLocation(int mode)
{
	if (mode == 0) return GetLocation();
	if (mode == 1) return entranceBarrier->GetLocation();
	if (mode == 2) return exitBarrier->GetLocation();
	if (mode == 3) return entranceSensor->GetLocation();
	if (mode == 4) return exitSensor->GetLocation();
	
	return Vector();
}

void CardReader::BarrierSetup(CarPark& carParkObj)
{
	entranceBarrier = new Barrier(carParkObj);
	exitBarrier = new Barrier(carParkObj);

	entranceBarrier->SetLocation(*new Vector(1.20f, 1.15f, 2.f));
	exitBarrier->SetLocation(*new Vector(20.f, 20.15f, 2.f));
}

void CardReader::SensorSetup(CarPark& carParkObj)
{
	entranceSensor = new Sensor(carParkObj, 1.5f);
	exitSensor = new Sensor(carParkObj, 1.5f);

	entranceSensor->SetLocation(*new Vector(1.10f, 1.05f, 1.5f));
	exitSensor->SetLocation(*new Vector(19.90f, 20.05f, 1.5f));
}

void CardReader::ActivateSensor(float vehicleWeight, bool inOut)
{
	// if inOut is true then call entrance sensor class
	if (inOut) entranceSensor->ActivateTrigger(vehicleWeight);
	else exitSensor->ActivateTrigger(vehicleWeight);
}

void CardReader::VehicleIncrement(std::string membershipID, std::vector<Card>* card)
{
	// Entrance sensor
	ActivateSensor((float)NumberInput("Enter car weight: "), true);
	ClearSystem();

	if (!entranceSensor->GetStatus())
	{
		std::cout << "\t\t\tUser Interaction Menu\n\n";
		std::cout << "No car detected | Override Allowed\n\n";

		PauseSystem();
		ClearSystem();
	}
	
	if (UserInterface(membershipID, card))
	{
		entranceBarrier->SetState(true); // opens entrance barrier
		if (entranceBarrier->GetState()) std::cout << "Barrier Open: Please drive through!\n";

		PauseSystem();
		ClearSystem();

		entranceBarrier->SetState(false); // closes entrance barrier
		if (!entranceBarrier->GetState()) std::cout << "Barrier Closed\n";
	}
}

void CardReader::VehicleDecrement()
{
	DisplaySpaces();
	DeallocateParkingSpace(TextInput("Enter Parking Space ID: "));
}

void CardReader::SetLocation(Vector& vec) { SetVector(vec.GetVector(0), vec.GetVector(1), vec.GetVector(2)); }

Vector CardReader::GetLocation() { return Vector(GetVector(0), GetVector(1), GetVector(2)); }

std::string CardReader::GetParkStatusMessage(int parkingSpace, std::string parkingSpaceID)
{
	int availabilityStatus = GetAvailabilityStatus();

	// only continue if car park is not full
	if (availabilityStatus != -31)
	{
		if (parkingSpace == 0 && availabilityStatus != -30) return "Proceed to " + parkingSpaceID;
		if (parkingSpace == 1 && availabilityStatus != -18) return "Proceed to " + parkingSpaceID;
		if (parkingSpace == 2 && availabilityStatus != -13) return "Proceed to " + parkingSpaceID;
	}
		
	return "Please exit the car park."; // could send them back to the selection.

	DisplaySpaces();
}

bool CardReader::UserInterface(std::string membershipID, std::vector<Card>* card)
{
	std::string errorMsg = "Invalid Card";
	bool bPaymentStatus = false;

	if (card == nullptr)
	{
		bPaymentStatus = PaymentMethod();
		errorMsg = "";
	}
	else
	{
		for (int i = 0; i < card->size(); i++)
			if (card->at(i).membershipID == membershipID)
			{
				bPaymentStatus = PaymentMethod(card->at(i).membershipType);
				errorMsg = "";
			}
	}


	std::cout << errorMsg << std::endl;

	if (errorMsg == "")
		ParkingMethod();

	return bPaymentStatus;
}

bool CardReader::PaymentMethod(std::string membershipType)
{
	int menu;
	bool bPaymentStatus = false;

	if (membershipType == "V" || membershipType == "v")
	{
		std::cout << "Card Accepted." << std::endl;
		bPaymentStatus = true;
	}

	else
	{
		menu = (int)NumberInput("\t\t\tUser Interaction Menu\n\n1) Card | 2) NFC (Contactless)\n\nYour Value: ");

		if (menu < 1 && menu > 2)
		{
			ClearSystem();
			PaymentMethod(membershipType);
		}

		if (menu == 1)
		{
			// For show
			std::cout << "Place Card" << std::endl;

			PauseSystem();
			ClearSystem();

			std::cout << "Please wait..." << std::endl;
			TextInput("Please enter pincode: ");

			ClearSystem();

			std::cout << "Accepted" << std::endl;
			bPaymentStatus = true;
		}

		else
		{
			std::cout << "Please wait..." << std::endl;
			std::cout << "Accepted" << std::endl;
			bPaymentStatus = true;
		}
	}

	PauseSystem();
	ClearSystem();

	return bPaymentStatus;
}

void CardReader::ParkingMethod()
{
	DisplaySpaces();

	int menu;
	menu = (int)NumberInput("\t\t\tUser Interaction Menu\n\nAny Special Places Required n(0/1)y: ");

	if (menu == 1) menu = (int)NumberInput("\nSelect Type: 1) Child | 2) Disabled: ");
	else menu = 0;

	std::cout << GetParkStatusMessage(menu, AllocateParkingSpace(menu)) << std::endl;
}