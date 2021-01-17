/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

// Fun Fact: BarcodeSensor is named that way,
// as the sensor could be in a barcode reader,
// or in another type of object.


// A different approach with BarcodeSensor and NumberPlateSensor, 
// instead of them deriving from Barcode Sensor, they'll be 
// called from their 'parent' class (IDReader) 
// Most likely bad practice, but to show a solution to Circular Dependency.

#pragma once

#include "IDReaders.h"

struct Card;
struct Barcodes;

class BarcodeSensor : private Functions
{
	protected:
		// These will be used to help the barcode scanner cross reference.
		std::vector<struct Barcodes>* barcodeDatabase;
		std::vector<struct Card>* userCardDatabase;

	public:
		BarcodeSensor();
		~BarcodeSensor();

		void OperateScanner(std::vector<struct Barcodes>* barcodeDatabase, std::vector<struct Card>* userCardDatabase);

	private:
		void UpdateVectors(std::vector<struct Barcodes>* barcodeDatabase, std::vector<struct Card>* userCardDatabase);
		void SubmitQuery(std::string query);
};