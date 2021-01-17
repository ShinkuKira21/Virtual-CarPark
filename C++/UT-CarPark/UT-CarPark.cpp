/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "pch.h"
#include "CppUnitTest.h"
#include "../Parking Methods/CarPark.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
	ERROR HISTORY: 
	
	Empty
*/


namespace UTCarPark
{
	TEST_CLASS(UTCarPark)
	{
		protected:
			const int error = -15;

		public:
			// JUPYTER TESTS (To Confirm Theory) - All Error Codes have to be UNIQUE
			// These error codes, will help the signs and other objects within the Car Park
			// to know what's going on.
			// Check Out -- https://github.com/ShinkuKira21/Virtual-CarPark/blob/master/Jupyter/Sign%20Operators.ipynb
			TEST_METHOD(UTAvailabiltyErrorCodes_EmptySpaces)
			{
				// All Spaces are Empty (Error code: -15)
				Assert::AreEqual(-15, Paths(false, false, false));
			}

			TEST_METHOD(UTAvailabiltyErrorCodes_GeneralSpaces)
			{
				// General Spaces are Full (Error code: -30)
				Assert::AreEqual(-30, Paths(true, false, false));
			}

			TEST_METHOD(UTAvailabiltyErrorCodes_DisabledSpaces)
			{
				// Disabled Spaces are Full (Error code: -13)
				Assert::AreEqual(-13, Paths(false, true, false));
			}

			TEST_METHOD(UTAvailabiltyErrorCodes_ChildSpaces)
			{
				// Child Spaces are Full (Error code: -18)
				Assert::AreEqual(-18, Paths(false, false, true));
			}

			TEST_METHOD(UTAvailabilityErrorCodes_GeneralSpacesAndDisabledSpaces)
			{
				// General Spaces and Disability Spaces are Full (Error code: -28)
				Assert::AreEqual(-28, Paths(true, true, false));
			}

			TEST_METHOD(UTAvailabiltyErrorCodes_GeneralSpacesAndChildSpaces)
			{
				// General and Child Spaces are Full (Error code: -33)
				Assert::AreEqual(-33, Paths(true, false, true));
			}

			TEST_METHOD(UTAvailabiltyErrorCodes_DisabilityAndChildSpaces)
			{
				// Disability and Child Spaces are Full (Error code: -16)
				Assert::AreEqual(-16, Paths(false, true, true));
			}

			TEST_METHOD(UTAvailabiltyErrorCodes_FullSpaces)
			{
				// All Spaces are Full (Error Code: -31)
				Assert::AreEqual(-31, Paths(true, true, true));
			}

		protected:
			int Paths(bool generalSpaces, bool disabledSpaces, bool childSpaces)
			{
				int err = error;
				if (generalSpaces) err -= 15;
				if (disabledSpaces) err += 2;
				if (childSpaces) err -= 3;
				return err;
			}
	};
}

namespace UTCardReader
{

}
