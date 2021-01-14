#pragma once
#include "CarPark.h"

class Sign : private CarPark
{
	protected:

	public:
		Sign(CarPark& carParkObj);
		~Sign();

		virtual std::string GetParkStatusMessage(int parkingSpace = NULL, std::string parkingSpaceID = "") override;

		virtual void SetLocation(Vector& vec);
		virtual Vector GetLocation();
	private:
		void DisplayText();
};

