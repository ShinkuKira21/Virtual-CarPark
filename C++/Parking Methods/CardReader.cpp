#include "CardReader.h"

// Card Memberships
CardReader::CardReader(CarPark& carParkObj, std::string membershipID, std::vector<Card>* card) : CarPark(carParkObj)
{
	BarrierSetup(carParkObj);

	std::string errorMsg = "Invalid Card";

	if (card == nullptr)
	{
		PaymentMethod();
		errorMsg = "";
	}
	else
	{
		for (int i = 0; i < card->size(); i++)
			if (card->at(i).membershipID == membershipID)
			{
				PaymentMethod(card->at(i).membershipType);
				errorMsg = "";
			}
	}
		
			
	std::cout << errorMsg << std::endl;

	if(errorMsg == "")
		ParkingMethod();

	PauseSystem();
	ClearSystem();
}

CardReader::~CardReader() { }

void CardReader::BarrierSetup(CarPark& carParkObj)
{
	entranceBarrier = new Barrier(carParkObj);
	exitBarrier = new Barrier(carParkObj);

	entranceBarrier->SetLocation(*new Vector(1.20f, 1.15f, 2.f));
	exitBarrier->SetLocation(*new Vector(20.f, 20.15f, 2.f));
}

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

void CardReader::PaymentMethod(std::string membershipType)
{
	int menu;

	if (membershipType == "V" || membershipType == "v")
		std::cout << "Card Accepted." << std::endl;

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
		}

		else
		{
			std::cout << "Please wait..." << std::endl;
			std::cout << "Accepted" << std::endl;
		}
	}

	PauseSystem();
	ClearSystem();
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