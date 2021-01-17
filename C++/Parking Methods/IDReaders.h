#pragma once

#include "CarPark.h"

struct Barcodes;
struct NumberPlates;

class IDReaders : private Functions
{
	protected:
		// These structs are multipurpose, they will act like a database,
		// they will also be a way of holding data.
		Barcodes* barcodeObj;
		NumberPlates* numberPlateObj;

		// A vector array to demonstrate the two databases
		std::vector<struct Barcodes> barcodeDatabase;
		std::vector<struct NumberPlates> numberPlateDatabase;

	public:
		IDReaders();
		~IDReaders();

		void UserInteraction();
	private:
		void Options(int uiMode);
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