/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "../../Library/Functions.h"

#include "IDReaders.h" // Task 2

#include "CardReader.h"
#include "Sign.h"
#include "Barrier.h"

//Enables input into the CarPark class and it's subclasses
Functions func;

void RegisterUserCard(int* lengthCards, std::vector<struct Card>* aCards, IDReaders* idReaders);
void SwipeCard(CarPark& cp, std::vector<struct Card>* aCards);
void LocationDetails(CarPark* cp, Sign* sign);

/* Debugging / Demonstration */
void DisplayMembershipIDs(std::vector<struct Card>* aCards);

int main()
{	
	// Task 2
	IDReaders* idReaders = new IDReaders();

	// creates car park with initial available spaces prefrences
	CarPark* cp = new CarPark(2, 1, 1);
	cp->SetLocation(*new Vector(35.f, -25.35f, 45.f)); // sets location

	Sign* sign; // declares the sign class object

	// declares a vector that casts the card struct
	std::vector<struct Card> cards;
	int lengthCards = 0; // sets lengthCards to 0
	
	while (true)
	{
		// creates a new sign with a up-to-date version of the carPark class.
		sign = new Sign(*cp->GetClass());
		sign->SetLocation(*new Vector(2.50f, 2.50f, 2.50f)); // sets location of sign 

		//asks user for their options
		int interactionBoard = (int)func.NumberInput("\t\t\tUser Interaction Menu\n\n1) Register User\t2) Swipe Card\n3) Drive Away\t\t4) Location Information\n\n5) Additional Features\t\t6+) Exit\n\nYour Input: ");
		
		func.ClearSystem();

		if (interactionBoard == 1) RegisterUserCard(&lengthCards, &cards, idReaders);
		else if (interactionBoard == 2) SwipeCard(*cp->GetClass(), &cards);
		else if (interactionBoard == 3) new CardReader(*cp->GetClass(), 0);
		else if (interactionBoard == 4) LocationDetails(cp->GetClass(), sign);
		else if (interactionBoard == 5) idReaders->UserInteraction();
		else break;

		func.ClearSystem();
	}
		
	cards.clear();
	delete cp;
	return 0;
}

void RegisterUserCard(int* aLength, std::vector<struct Card>* aCards, IDReaders* idReaders)
{
	// adds a new object to the aCards vector pointer
	aCards->push_back(Card());
	
	// if aLength is 0 then set id as 0
	if (*aLength == 0) aCards->at(0).membershipID = '0';
	// adds 1 to aCards membershipID attribute from last membershipID (will always be UNIQUE)
	else aCards->at(*aLength).membershipID = std::to_string((int)func.TextToNumber(aCards->at(*aLength-1).membershipID) + 1);

	aCards->at(*aLength).memberName = func.TextInput("Enter member name: "); // asks user to enter name
	aCards->at(*aLength).membershipType = func.TextInput("Enter membership type ([V|istor][S|taff]): "); // asks user to enter V for visitor or S for staff

	if (aCards->at(*aLength).membershipType == "S" || aCards->at(*aLength).membershipType == "s")
		aCards->at(*aLength).department = func.TextInput("Enter department: ");

	aCards->at(*aLength).expiryDate = func.TextInput("Enter expiry date (Dd/Mm/yyyy), Ex: (3/9/2022): "); // asks user to enter expiry date.

	// Adds a barcode to new membership card. (Task 2)
	idReaders->AddBarcode(aCards->at(*aLength).membershipID, aCards);

	// increments aLength by 1 (noticed *aLength++ does not work)
	*aLength = *aLength + 1;

	func.ClearSystem();
}

void SwipeCard(CarPark& cp, std::vector<struct Card>* aCards)
{
	// declares a CardReader named cReader
	CardReader* cReader;
	std::string memID; // holds membershipID
	
	func.ClearSystem();

	DisplayMembershipIDs(aCards);

	// asks user to type in the membership ID
	if (aCards->size() != 0)
	{
		memID = std::to_string((int)func.NumberInput("Enter Membership ID: "));
		cReader = new CardReader(cp, 1, memID, aCards);
	}
	else
	{
		std::cout << func.ColorText("No Membership Cards Available\n\n", 37, 41);
		func.PauseSystem();
	}
	
}

void LocationDetails(CarPark* cp, Sign* sign)
{
	/* The following shows location data,
	*  the method of using Color syntax,
	*  helped me develop the Functions.h
	*  for to help create the Task 2 elements 
	*  in this project.
	*/

	Vector location;

	//system("COLOR 02");

	// carpark location
	location = cp->GetLocation();

	func.ClearSystem();
	std::cout << "\t\t\t\033[1;35m Location Information | Car Park\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m "<< location.GetVector(2) << std::endl << std::endl;

	// sign location
	location = sign->GetLocation();

	std::cout << "\t\t\t\033[1;35m                      | Sign\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	// card reader location

	CardReader* cr = new CardReader(*cp, 2);
	location = cr->GetSubclassLocation(0);

	std::cout << "\t\t\t\033[1;35m                      | Card Reader\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	// entrance barrier location

	location = cr->GetSubclassLocation(1);

	std::cout << "\t\t\t\033[1;35m                     | Card Reader | Entrance Barrier\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	// entrance sensor location

	location = cr->GetSubclassLocation(3);

	std::cout << "\t\t\t\033[1;35m                     | Card Reader | Entrance Sensor\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	// exit barrier location

	location = cr->GetSubclassLocation(2);

	std::cout << "\t\t\t\033[1;35m                     | Card Reader | Exit Barrier\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	// exit sensor location

	location = cr->GetSubclassLocation(4);

	std::cout << "\t\t\t\033[1;35m                     | Card Reader | Exit Sensor\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	delete cr;

	func.PauseSystem();
}

void DisplayMembershipIDs(std::vector<struct Card>* aCards)
{
	std::cout << "\t\t\tUser Interaction Menu | Demonstration Mode\n\n";
	
	for (int i = 0; i < aCards->size(); i++)
	{
		std::cout << "ID: " << aCards->at(i).membershipID << " | Type: " << aCards->at(i).membershipType << " | ";
		
		if (aCards->at(i).membershipType == "S" || aCards->at(i).membershipType == "s")
			std::cout << "Department: " << aCards->at(i).department << " | ";

		std::cout << "Name: " << aCards->at(i).memberName << " | Current Date: " << func.GetStringDate() << " | Expiry Date: " << aCards->at(i).expiryDate << std::endl;
	}
		

	std::cout << std::endl;
}
