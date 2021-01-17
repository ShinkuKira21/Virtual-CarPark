#pragma once

#include "CarPark.h"
#include "CardReader.h"

struct Barcodes;
struct NumberPlates;

class IDReaders : private Functions
{
	protected:
		// These structs are multipurpose, they will act like a database,
		// they will also be a way of holding data.
		Barcodes* barcodeObj;
		NumberPlates* numberPlateObj;
		
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
	std::string numberplate;
};