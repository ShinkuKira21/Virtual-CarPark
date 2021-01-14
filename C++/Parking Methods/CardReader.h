#pragma once
#include "CarPark.h"
#include "Barrier.h"
#include "Sensors.h"

class CardReader : private CarPark
{
	protected:
		class Barrier* entranceBarrier;
		class Barrier* exitBarrier;

		class Sensor* entranceSensor;
		class Sensor* exitSensor;

	public:
		CardReader(CarPark& carParkObj, int mode, std::string membershipID = "", std::vector<struct Card>* card = nullptr);
		~CardReader();

	private:
		virtual void SetLocation(Vector& vec);
		virtual std::string GetParkStatusMessage(int parkingSpace, std::string parkingSpaceID) override;

		void BarrierSetup(CarPark& carParkObj);
		void SensorSetup(CarPark& carParkObj);
		void ActivateSensor(float vehicleWeight, bool inOut);

		void VehicleIncrement(std::string membershipID, std::vector<Card>* card);
		void VehicleDecrement();

		bool UserInterface(std::string membershipID, std::vector<Card>* card);
		bool PaymentMethod(std::string membershipType = "");
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

