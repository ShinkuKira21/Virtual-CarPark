/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#pragma once

#include "IDReaders.h"

struct NumberPlates;

class NumberPlateSensor : private Functions
{
	protected:
		std::vector<struct NumberPlates>* numberPlateDatabase;
	public:
		NumberPlateSensor();
		~NumberPlateSensor();

		void OperateScanner(std::vector<struct NumberPlates>* numberPlateDatabase);

	private:
		void UpdateVectors(std::vector<struct NumberPlates>* numberPlateDatabase);
		void SubmitQuery(std::string query);
};