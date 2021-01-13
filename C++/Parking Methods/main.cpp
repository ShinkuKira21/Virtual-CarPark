#include "../../Library/Functions.h"

#include "CardReader.h"
#include "Sign.h"
#include "Barrier.h"
//Enables input into the CarPark class and it's subclasses
Functions func;

void RegisterUserCard(int* lengthCards, std::vector<struct Card>* aCards);
void SwipeCard(CarPark& cp, std::vector<struct Card>* aCards);

int main()
{	
	CarPark* cp = new CarPark(2, 1, 1);
	cp->SetLocation(*new Vector(35.f, -25.35f, 45.f));

	Sign* sign;

	std::vector<struct Card> cards;
	int lengthCards = 0;
	
	while (true)
	{
		sign = new Sign(*cp->GetClass());
		sign->SetLocation(*new Vector(2.50f, 2.50f, 2.50f));

		int interactionBoard = (int)func.NumberInput("\t\t\tUser Interaction Menu\n\n1) Register User\t2) Swipe Card\n3) Drive Away\t\t4) Exit\n\nYour Input: ");
		
		func.ClearSystem();

		if (interactionBoard == 1) RegisterUserCard(&lengthCards, &cards);
		else if (interactionBoard == 2) SwipeCard(*cp->GetClass(), &cards);
		else if (interactionBoard == 3) new CardReader(*cp->GetClass(), 0);
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