/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "BarcodeSensor.h"

BarcodeSensor::BarcodeSensor() { }

BarcodeSensor::~BarcodeSensor() { }

void BarcodeSensor::OperateScanner(std::vector<struct Barcodes>* barcodeDatabase, std::vector<struct Card>* userCardDatabase)
{
	// Update Vectors before using them
	UpdateVectors(barcodeDatabase, userCardDatabase);

	// This will be the query for the Barcode Scanner
	std::string qry = TextInput("Enter Barcode Scanner: ");
	SubmitQuery(qry);
}

void BarcodeSensor::UpdateVectors(std::vector<struct Barcodes>* barcodeDatabase, std::vector<struct Card>* userCardDatabase)
{
	this->barcodeDatabase = barcodeDatabase;
	this->userCardDatabase = userCardDatabase;
}

void BarcodeSensor::SubmitQuery(std::string query)
{
	ClearSystem();

	// if true then match has been found
	bool bFoundBarcode = false;

	// Find Query of Barcode
	for (int i = 0; i < barcodeDatabase->size(); i++)
	{
		if (barcodeDatabase->at(i).id == query)
		{
			// switches boolean to true
			bFoundBarcode = !bFoundBarcode;

			std::cout << "ID: " << barcodeDatabase->at(i).id << " | Membership ID: " << barcodeDatabase->at(i).membershipID << std::endl;

			for (int j = 0; j < userCardDatabase->size(); j++)
				if (userCardDatabase->at(j).membershipID == barcodeDatabase->at(i).membershipID)
					std::cout << "Name: " << userCardDatabase->at(j).memberName << " | Membership Type: " << userCardDatabase->at(j).membershipType << std::endl;
		}
	}

	// if bFoundBarcode is true then display "No User Found"
	if (!bFoundBarcode) std::cout << ColorText("No User Information Found\n\n", 37, 41);
		
	PauseSystem();
}
