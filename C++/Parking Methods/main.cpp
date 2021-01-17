/* Author: Edward Patch (1801492) - University of Wales Trinity St. Davids */

#include "../../Library/Functions.h"

#include "IDReaders.h" // Task 2

#include "CardReader.h"
#include "Sign.h"
#include "Barrier.h"

//Enables input into the CarPark class and it's subclasses
Functions func;

void RegisterUserCard(int* lengthCards, std::vector<struct Card>* aCards);
void SwipeCard(CarPark& cp, std::vector<struct Card>* aCards);
void LocationDetails(CarPark* cp, Sign* sign);

int main()
{	
	IDReaders* idReaders = new IDReaders();

	CarPark* cp = new CarPark(2, 1, 1);
	cp->SetLocation(*new Vector(35.f, -25.35f, 45.f));

	Sign* sign;

	std::vector<struct Card> cards;
	int lengthCards = 0;
	
	while (true)
	{
		sign = new Sign(*cp->GetClass());
		sign->SetLocation(*new Vector(2.50f, 2.50f, 2.50f));

		int interactionBoard = (int)func.NumberInput("\t\t\tUser Interaction Menu\n\n1) Register User\t2) Swipe Card\n3) Drive Away\t\t4) Location Information\n\n5) Additional Features\t\t6+) Exit\n\nYour Input: ");
		
		func.ClearSystem();

		if (interactionBoard == 1) RegisterUserCard(&lengthCards, &cards);
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

void RegisterUserCard(int* aLength, std::vector<struct Card>* aCards)
{
	aCards->push_back(Card());

	if (*aLength == 0) aCards->at(0).membershipID = '0';
	else aCards->at(*aLength).membershipID = std::to_string((int)func.TextToNumber(aCards->at(*aLength-1).membershipID) + 1);
	aCards->at(*aLength).memberName = func.TextInput("Enter member name: ");
	aCards->at(*aLength).membershipType = func.TextInput("Enter membership type ([V|istor][S|taff]): ");
	aCards->at(*aLength).expiryDate = func.TextInput("Enter expiry date (dd/mm/yy): ");

	std::cout << "Card ID: " << aCards->at(*aLength).membershipID;

	*aLength = *aLength + 1;

	func.ClearSystem();
}

void SwipeCard(CarPark& cp, std::vector<struct Card>* aCards)
{
	CardReader* cReader;
	std::string memID;

	bool bCardAvailable = (int)func.NumberInput("Is Card Available? n(0/1)y: ");
	
	func.ClearSystem();

	if (bCardAvailable)
	{
		memID = std::to_string((int)func.NumberInput("Enter Membership ID: "));
		cReader = new CardReader(cp, 1, memID, aCards);
	}
	else cReader = new CardReader(cp, 1);
}

void LocationDetails(CarPark* cp, Sign* sign)
{
	Vector location;

	//system("COLOR 02");

	location = cp->GetLocation();

	func.ClearSystem();
	std::cout << "\t\t\t\033[1;35m Location Information | Car Park\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m "<< location.GetVector(2) << std::endl << std::endl;

	location = sign->GetLocation();

	std::cout << "\t\t\t\033[1;35m                      | Sign\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	CardReader* cr = new CardReader(*cp, 2);
	location = cr->GetSubclassLocation(0);

	std::cout << "\t\t\t\033[1;35m                      | Card Reader\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	location = cr->GetSubclassLocation(1);

	std::cout << "\t\t\t\033[1;35m                     | Card Reader | Entrance Barrier\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	location = cr->GetSubclassLocation(3);

	std::cout << "\t\t\t\033[1;35m                     | Card Reader | Entrance Sensor\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	location = cr->GetSubclassLocation(2);

	std::cout << "\t\t\t\033[1;35m                     | Card Reader | Exit Barrier\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	location = cr->GetSubclassLocation(4);

	std::cout << "\t\t\t\033[1;35m                     | Card Reader | Exit Sensor\033[0m\n";
	std::cout << "\t\t\t\t\033[1;31mX:\033[0m " << location.GetVector(0) << ", \033[1;32mY:\033[0m " << location.GetVector(1) << ", \033[1;36mZ:\033[0m " << location.GetVector(2) << std::endl << std::endl;

	delete cr;

	func.PauseSystem();
}
