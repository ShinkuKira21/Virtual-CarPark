/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "IDReaders.h"
#include "BarcodeSensor.h"
#include "NumberPlateSensor.h"

IDReaders::IDReaders() { }

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

	// the fix to the circular dependency,
	// is via forward declarations, and avoid cross referencing headers
	// could be improved, however, this was to demonstrate the cross
	// circular dependency problem.
	BarcodeSensor* barcodeReader = new BarcodeSensor();
	NumberPlateSensor* numPlateSensor = new NumberPlateSensor();

	if (uiMode == 1) ShowBarcodes();
	if (uiMode == 2) barcodeReader->OperateScanner(&barcodeDatabase, cards);
	if (uiMode == 3) AddNumberPlate();
	if (uiMode == 4) numPlateSensor->OperateScanner(&numberPlateDatabase);
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

void IDReaders::AddNumberPlate()
{
	// Adds a NumberPlate to vector object
	numberPlateDatabase.push_back(NumberPlates());

	// Car Registrations are already unique.
	numberPlateDatabase.at(numberPlateDatabase.size() - 1).carRegistration = TextInput("Input Car Registration: ");

	//Asks user for make/model, colour and milage
	numberPlateDatabase.at(numberPlateDatabase.size() - 1).carMakeModel = TextInput("Input Car Make/Model: ");
	numberPlateDatabase.at(numberPlateDatabase.size() - 1).carColour = TextInput("Input Car Colour: ");
	numberPlateDatabase.at(numberPlateDatabase.size() - 1).carMilage = TextInput("Input Car Milage: ");
}