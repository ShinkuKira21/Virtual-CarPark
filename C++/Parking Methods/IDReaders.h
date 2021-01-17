/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#pragma once

#include "CardReader.h"

struct Barcodes;
struct NumberPlates;

class IDReaders : private Functions
{
	protected:
		// A vector object to demonstrate the two databases
		std::vector<struct Barcodes> barcodeDatabase;
		std::vector<struct NumberPlates> numberPlateDatabase;

		// A vector pointer to demonstrate the cards database
		std::vector<struct Card>* cards;

	public:
		IDReaders();
		~IDReaders();

		void UserInteraction();
		void AddBarcode(std::string membershipID, std::vector<struct Card>* card);

	private:
		void Options(int uiMode);
		void ShowBarcodes();
		void AddNumberPlate();
};

struct Barcodes
{
	std::string id;
	std::string membershipID;
};

struct NumberPlates
{
	// You only need the numberplate number, 
	// then search the number through a database.
	std::string carRegistration;

	// Database Side:
	std::string carMakeModel;
	std::string carColour;
	std::string carMilage;
};