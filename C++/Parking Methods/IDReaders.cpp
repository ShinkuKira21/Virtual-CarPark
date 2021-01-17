#include "IDReaders.h"

IDReaders::IDReaders()
{
}

IDReaders::~IDReaders() { }

void IDReaders::UserInteraction()
{
	std::cout << "\t\t\tUser Interaction Menu\n\n";
	std::cout << "1) Register a Barcode\t\t2) Read a Barcode\n";
	std::cout << "3) Register a Number Plate\t4) Read a Number Plate";

	int uiMode = (int)NumberInput("\n\nYour Input: ");

	Options(uiMode);
}

void IDReaders::Options(int uiMode)
{
	if (uiMode < 1 || uiMode > 4)
	{
		// The ColorText function is a new member of the Functions class.
		std::cout << ColorText("Error: exceeded parameters.\n\n", 37, 41);
		PauseSystem();
		ClearSystem();

		UserInteraction();
	}

	if (uiMode == 1) return;
	if (uiMode == 2) return;
	if (uiMode == 3) return;
	if (uiMode == 4) return;
}
