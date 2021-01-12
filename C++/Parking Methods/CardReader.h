#pragma once
#include "CarPark.h"
#include "Barrier.h"
class CardReader : private CarPark
{
	protected:
		class Barrier* entranceBarrier;
		class Barrier* exitBarrier;

	public:
		CardReader(CarPark& carParkObj, std::string membershipID = "", std::vector<struct Card>* card = nullptr);
		~CardReader();

	private:
		virtual std::string GetParkStatusMessage(int parkingSpace, std::string parkingSpaceID) override;

		void BarrierSetup(CarPark& carParkObj);
		void PaymentMethod(std::string membershipType = "");
		void ParkingMethod();	
};


// Card could link to the database (via the membershipID)
struct Card
{
	// Database
	std::string membershipID; // Unique IDs to link with database
	std::string memberName; // Card Reader could output member's name
	std::string membershipType; // membership type
	std::string department; // if membershipType is Staff, the department will become required.

	// Card Details
	std::string typeOfCard; // Visitor Card or Staff Card
	std::string expiryDate; // If expired, sign will tell user to enter the carpark, and report to office to renew their membership or drive around carpark and approach exit barrier.
};

