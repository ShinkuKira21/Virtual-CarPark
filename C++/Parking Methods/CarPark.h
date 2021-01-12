#pragma once
#include "../../Library/Functions.h"
#include "Vector.h"

class CarPark : public Functions, protected Vector
{
	// this-> current class
	// carPark-> sub obj class
	public:
		// I was thinking of what I do in Unreal Engine. 
		// Store everything in a sub object then 
		// reuse the same obj for different child classes?
		// not sure if there's a better way...
		CarPark* carPark;

		int totalSpaces;

		// Defaults
		int availableGeneralSpaces, availableDisabilitySpaces, 
			availableChildSpaces;
		int usedGeneralSpaces, usedDisabilitySpaces, usedChildSpaces;

		const std::string parkingSpaceIDs[3] = { "CG-PS-", "CH-PS-", "CD-PS-" };
		std::string* parkingSpaceID;
		std::string* parkingSpaceStatus;

	public:
		CarPark(CarPark& cPark);
		CarPark(int gSpaces, int dSpaces, int cSpaces);
		~CarPark();

		class CarPark* GetClass();

		std::string AllocateParkingSpace(int parkingType);
		void DeallocateParkingSpace(std::string parkingSpaceID);

		int GetAvailabilityStatus();
		std::string GetParkingSpaceNumber();
		void CountAvailableSpaces();

		virtual void SetLocation(Vector& vec) override;

		// The message can be customised, 
		// depending on where the message is displayed.
		virtual std::string GetParkStatusMessage(int parkingSpace = NULL, std::string parkingSpaceID = "") 
		{ 
			if(GetAvailabilityStatus() != -2) return "Success: Spaces Available";
			return "Error: Car Park is full.";
		}

		virtual void DisplaySpaces()
		{
			for (int i = 0; i < carPark->totalSpaces; i++)
			{
				std::cout << "Parking Space ID: " + carPark->parkingSpaceID[i] << "\t\t";
				std::cout << "Parking Space Status: " + carPark->parkingSpaceStatus[i];
				std::cout << "\n";
			}
		}

	private:
		CarPark();
		
		void InitialiseParkingSlotIDs();
};