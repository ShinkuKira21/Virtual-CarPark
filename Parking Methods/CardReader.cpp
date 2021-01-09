#include "CardReader.h"

// Card Memberships
CardReader::CardReader(CarPark& carParkObj, std::string membershipID, std::vector<Card>* card) : CarPark(carParkObj)
{
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

std::string CardReader::GetParkStatusMessage(int parkingSpace, std::string parkingSpaceID)
{
	if (parkingSpace == 0 && GetAvailabilityStatus() != -30) return "Proceed to " + parkingSpaceID;
	if (parkingSpace == 1 && GetAvailabilityStatus() != -18) return "Proceed to " + parkingSpaceID;
	if (parkingSpace == 2 && GetAvailabilityStatus() != -13) return "Proceed to " + parkingSpaceID;
	return "Please exit the car park."; // could send them back to the selection.
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
	int menu;
	menu = (int)NumberInput("\t\t\tUser Interaction Menu\n\nAny Special Places Required n(0/1)y: ");

	if (menu == 1) menu = (int)NumberInput("\nSelect Type: 1) Child | 2) Disabled: ");
	else menu = 0;

	std::cout << GetParkStatusMessage(menu, AllocateParkingSpace(menu)) << std::endl;
}