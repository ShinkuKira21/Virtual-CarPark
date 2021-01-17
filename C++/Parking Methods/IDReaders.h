#pragma once

#include "CarPark.h"

class IDReaders
{
	protected:
		// These structs are multipurpose, they will act like a database,
		// they will also be a way of holding data.
		struct Barcodes barcodeObj;
		struct NumberPlates numberPlateObj;

		// A vector array to demonstrate the two databases
		std::vector<struct Barcodes> barcodeDatabase;
		std::vector<struct NumberPlates> numberPlateDatabase;

	public:
		IDReaders();
		~IDReaders();
	private:

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