/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "NumberPlateSensor.h"

NumberPlateSensor::NumberPlateSensor() { }

NumberPlateSensor::~NumberPlateSensor() { }

void NumberPlateSensor::OperateScanner(std::vector<struct NumberPlates>* numberPlateDatabase)
{
	// Update Vectors before using them
	UpdateVectors(numberPlateDatabase);

	// This will be the query for the Car Registration
	std::string qry = TextInput("Enter Car Registration: ");
	SubmitQuery(qry);
}

void NumberPlateSensor::UpdateVectors(std::vector<struct NumberPlates>* numberPlateDatabase)
{
	this->numberPlateDatabase = numberPlateDatabase;
}

void NumberPlateSensor::SubmitQuery(std::string query)
{
	ClearSystem();

	bool bFoundCarReg = false;

	for (int i = 0; i < numberPlateDatabase->size(); i++)
	{
		if (numberPlateDatabase->at(i).carRegistration == query)
		{
			// switches boolean to true
			bFoundCarReg = !bFoundCarReg;

			std::cout << "Car Registration: " << ColorText(numberPlateDatabase->at(i).carRegistration, 30, 43, 3) << " | Car Make/Model: " << numberPlateDatabase->at(i).carMakeModel << "\nCar Color: " << numberPlateDatabase->at(i).carColour << " | Car Milage: " << numberPlateDatabase->at(i).carMilage << " Mi" << std::endl;
		}
	}

	// Find Query of Cars

	// if this happens car has no reg or reg is newly registered on dvla's
	// database
	if (!bFoundCarReg) std::cout << ColorText("Error: Car Not Found\n\n", 37, 41);

	PauseSystem();
}
