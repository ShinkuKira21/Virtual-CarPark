/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "pch.h"
#include "CppUnitTest.h"

#include "../../Library/Functions.h"
#include "../Parking Methods/CarPark.h" // Car Park
#include "../Parking Methods/CardReader.h" // Card Reader
#include "../Parking Methods/IDReaders.h" // IDReaders

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
	ERROR HISTORY: 
	
	UTCardReader

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

		private:
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
	TEST_CLASS(UTCardReader)
	{
		protected:
			Functions func;

			struct Card cards;

			std::vector<struct Card> vecCards;

			const std::string testTypeData[6] = { "V", "s", "v", "V", "S", "s" };
			const std::string testNameData[6] = { "Jason Davies", "Mary Anderson", "Travis Smith", "Jessica Emmerfield", "Jack Grill", "Jessie Jackson" };
			const std::string testExpiryDates[6] = { "26/07/2023", "17/03/2022", "19/01/2021", "31/03/2021", "26/04/2022", "15/02/2024" };		

		public:
			TEST_METHOD(UTCardStruct_Testing)
			{
				// Testing the Card Struct 
				cards.membershipID = "0";
				Assert::AreEqual(cards.membershipID, std::string("0"));
			}

			TEST_METHOD(UTCardStruct_VectorMembershipAlgorithm)
			{
				/* Tests Conducted: 4 | Information: One Error: SetupUserCards() Failed | TextToNumber() */

				// Adds 6 user cards to the vecCards Vector
				SetupUserCards(6);

				// Checks if each ID goes up in a increment of 1, from zero
				for (int i = 0; i < vecCards.size(); i++)
					Assert::AreEqual(std::to_string(i), vecCards.at(i).membershipID);

				ClearUserCards();
			}

			TEST_METHOD(UTCardStruct_ComparisonErrorCheck)
			{
				/* Tests Conducted: 6 | Information: No errors */

				SetupUserCards(6);

				// Test checks if the information would return with string error
				for(int i = 0; i < 6; i++)
					Assert::IsTrue(CheckData(std::to_string(i)).size() > 0);

				ClearUserCards();
			}

			TEST_METHOD(UTCardStruct_UserRecordIntegrity)
			{
				/* Tests Conducted: 2 | Information: No Errors */
				SetupUserCards(6);

				// Test checks if user card data, matches with test data where membership ID is matched.
				for (int i = 0; i < vecCards.size(); i++)
					Assert::AreEqual(testNameData[i], CheckData(std::to_string(i)).at(0).memberName);
			}

		private:
			void SetupUserCards(int userCards)
			{
				for (int i = 0; i < userCards; i++)
				{
					vecCards.push_back(Card());

					// if vecCards vector size is equal to 1 then set initial ID to 0
					if (vecCards.size() == 1) vecCards.at(0).membershipID = "0";
					// set vecCard at current index, with the membershipID of last index, and add one to the index. (After converting TextToNumber)
					else vecCards.at(i).membershipID = std::to_string((int)func.TextToNumber(vecCards.at(i-1).membershipID) + 1);

					// fills vecCards with test data
					vecCards.at(i).membershipType = testTypeData[i];
					vecCards.at(i).memberName = testNameData[i];
					vecCards.at(i).expiryDate = testExpiryDates[i];	
				}
			}

			void ClearUserCards() { vecCards.clear(); }

			std::vector<struct Card> CheckData(std::string membershipID)
			{
				std::vector<struct Card> cardInfo;

				for (int i = 0; i < vecCards.size(); i++)
					if (vecCards.at(i).membershipID == membershipID)
						cardInfo.push_back(vecCards.at(i));
					
				return cardInfo;
			}
	};
}

namespace UTIDReaders
{
	TEST_CLASS(UTIDReaders)
	{
		protected:
			Functions func;

			std::vector<struct Barcodes> barcodeDatabase;
			std::vector<struct NumberPlates> numberPlateDatabase;

		public:
			TEST_METHOD(UTBarcodes_TestBarcodeIDLinker)
			{
				/* Tests Conducted: 1 | Information: No Errors */
				LinkBarcodes(std::to_string(0));
				Assert::IsTrue(SubmitBarcodeQuery("BC-0"));
			}
			
			TEST_METHOD(UTCarNumberPlate_TestCarRegSensor)
			{
				/* Tests Conducted: 1 | Information: No Errors */
				AddNumberPlate("T12 UIF", "Bentley Arnage", "Blue", "2,983");

				AddNumberPlate("T252 MAP", "Mercedes CLK 2000 Elegance", "Silver", "32,983");

				// Number Plate should Exist
				Assert::IsTrue(SubmitCarRegQuery("T12 UIF"));

				// Number Plate should fail
				// The spacing of number plate
				// makes the number plate illegal.
				Assert::IsFalse(SubmitCarRegQuery("T252MAP"));


				// Should fail, number plate isn't registered.
				Assert::IsFalse(SubmitBarcodeQuery("CE35 7IO"));
			}

		private:
			/* BARCODES SECTION */
			void LinkBarcodes(std::string memID)
			{
				barcodeDatabase.push_back(Barcodes());

				barcodeDatabase.at(barcodeDatabase.size() - 1).id = BarcodeIDAlgorithm();
				barcodeDatabase.at(barcodeDatabase.size() - 1).membershipID =
					memID;
			}

			std::string BarcodeIDAlgorithm()
			{
				// if size of barcodeDatabase is 0, set id to 'BC-0'
				if (barcodeDatabase.size() - 1 == 0)
					return "BC-0";

				// add one from last registered ID
				else return "BC-" + std::to_string((int)func.TextToNumber(barcodeDatabase.at(barcodeDatabase.size() - 2).id) + 1);
			}

			bool SubmitBarcodeQuery(std::string qryBarcodeID)
			{
				// if true then match has been found
				bool bFoundBarcode = false;

				// Find Query of Barcode
				// switches boolean to true
				for (int i = 0; i < barcodeDatabase.size(); i++)
					if (barcodeDatabase.at(i).id == qryBarcodeID)
						bFoundBarcode = !bFoundBarcode;

				return bFoundBarcode;
			}

			/* Car Number Plate Sensor*/

			void AddNumberPlate(std::string carReg, std::string carModel, std::string carColour, std::string carMilage)
			{
				// Adds a NumberPlate to vector object
				numberPlateDatabase.push_back(NumberPlates());

				// Car Registrations are already unique.
				numberPlateDatabase.at(numberPlateDatabase.size() - 1).carRegistration = carReg;

				//Asks user for make/model, colour and milage
				numberPlateDatabase.at(numberPlateDatabase.size() - 1).carMakeModel = carModel;
				numberPlateDatabase.at(numberPlateDatabase.size() - 1).carColour = carColour;
				numberPlateDatabase.at(numberPlateDatabase.size() - 1).carMilage = carMilage;
			}

			bool SubmitCarRegQuery(std::string query)
			{
				bool bFoundCarReg = false;

				for (int i = 0; i < numberPlateDatabase.size(); i++)
					if (numberPlateDatabase.at(i).carRegistration == query)
						bFoundCarReg = !bFoundCarReg;

				return bFoundCarReg;
			}
	};
}