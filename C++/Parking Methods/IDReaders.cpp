#include "IDReaders.h"

IDReaders::IDReaders()
{
}

IDReaders::~IDReaders() { }

void IDReaders::UserInteraction()
{
	std::cout << "\t\t\tUser Interaction Menu\n\n";
	std::cout << "1) List of Registered Barcodes\t\t2) Read a Barcode\n";
	std::cout << "3) Register a Number Plate\t\t4) Read a Number Plate";

	int uiMode = (int)NumberInput("\n\nYour Input: ");

	Options(uiMode);
}

void IDReaders::AddBarcode(std::string membershipID, std::vector<struct Card>* card)
{
	// transfers the card object from main to update the object data
	this->cards = card;

	// Adds a new barcode
	barcodeDatabase.push_back(Barcodes());

	// if size of barcodeDatabase is 0, set id to 'BC-0'
	if (barcodeDatabase.size() - 1 == 0)
		barcodeDatabase.at(0).id = "BC-0";

	// add one from last registered ID
	else barcodeDatabase.at(barcodeDatabase.size() - 1).id = "BC-" + std::to_string((int)TextToNumber(barcodeDatabase.at(barcodeDatabase.size() - 2).id) + 1);

	barcodeDatabase.at(barcodeDatabase.size() - 1).membershipID = membershipID;
}

void IDReaders::Options(int uiMode)
{
	if (uiMode < 1 || uiMode > 4)
	{
		// The ColorText function is a new member of the Functions class.
		std::cout << ColorText("Error: exceeded parameters.\n\n", 37, 41);
		PauseSystem();
		ClearSystem();

		UserInteraction();
	}

	ClearSystem();

	if (uiMode == 1) ShowBarcodes();
	if (uiMode == 2) return;
	if (uiMode == 3) return;
	if (uiMode == 4) return;
}

void IDReaders::ShowBarcodes()
{
	// Prints out the registered barcodes and linked user cards
	for (int i = 0; i < barcodeDatabase.size(); i++)
	{
		std::cout << "ID: " << barcodeDatabase.at(i).id << " | Membership ID: " << barcodeDatabase.at(i).membershipID << std::endl;

		for (int j = 0; j < cards->size(); j++)
			if (cards->at(j).membershipID == barcodeDatabase.at(i).membershipID)
				std::cout << "Name: " << cards->at(j).memberName << " | Membership Type: " << cards->at(j).membershipType << std::endl;
	}

	// if barcode database obj is empty pausesystem
	if(barcodeDatabase.size() != 0)
		PauseSystem();
}
