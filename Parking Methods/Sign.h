#pragma once
#include "CarPark.h"

class Sign : private CarPark
{
	protected:
	public:
		Sign(CarPark& carParkObj);
		~Sign();


		// Public just for testing procedures
		virtual std::string GetParkStatusMessage(int parkingSpace, std::string parkingSpaceID) override;
	private:
		
};

