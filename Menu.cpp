#include "pch.h"
#include "Menu.h"
#include <iostream>
Menu::Menu() : str(""), gridSize(-1), totalRounds(0), state("lvlOne")
{
	lvlOne();
}

void Menu::quit()
{
	std::cout << "Exiting program..." << std::endl;
	exit(0); // or set a flag to break menu loop
}

void Menu::lvlOne()
{
	state = "lvlOne";
	transitions.clear(); // Clear previous choices before adding new ones
	transitions.push_back(&Menu::lvlTwoEncryption);
	transitions.push_back(&Menu::lvlTwoDecryption);
	transitions.push_back(&Menu::quit);

	std::cout << "*****************************************************" << std::endl;
	std::cout << "Menu - Lvl 1" << std::endl;
	std::cout << "1. Encrypt a message" << std::endl;
	std::cout << "2. Decrypt a message" << std::endl;
	std::cout << "3. Quit" << std::endl;
	std::cout << "*****************************************************" << std::endl;

	transition();
}

void Menu::transition()
{
	if (prevState != state) {
		prevState = state; // Save the current state before transitioning
	}

	std::string line;
	while (true) {
		std::cout << "Enter choice: ";
		std::getline(std::cin, line);

		// Handle empty input (user just pressed Enter)
		if (line.empty()) {
			std::cout << "Input cannot be empty. Please enter an integer corresponding to the available choices." << std::endl;
			continue;
		}

		// Try to convert input to integer
		try {
			input = std::stoi(line);
		}
		catch (const std::invalid_argument&) {
			std::cout << "Invalid input. Please enter an integer corresponding to the available choices." << std::endl;
			continue;
		}
		catch (const std::out_of_range&) {
			std::cout << "Input is out of range. Please enter a valid integer." << std::endl;
			continue;
		}

		if (input < 1 || input > static_cast<int>(transitions.size())) {
			std::cout << "Invalid input. Please enter an integer corresponding to the available choices." << std::endl;
			continue;
		}
		break;
	}
	(this->*transitions[input - 1])(); // transition to the chosen state.
}

void Menu::lvlTwoEncryption()
{
	state = "lvlTwoEncryption";
	transitions.clear(); // Clear previous choices before adding new ones
	transitions.push_back(&Menu::setStr);
	transitions.push_back(&Menu::lvlThreeSingleEncryption);
	transitions.push_back(&Menu::lvlThreeMultiEncryption);
	transitions.push_back(&Menu::lvlOne);

	std::cout << "*****************************************************" << std::endl;
	std::cout << "Menu - Lvl 2 : Encryption" << std::endl;
	std::cout << "1. Enter a message" << std::endl;
	std::cout << "2. One-round encryption" << std::endl;
	std::cout << "3. Automatic multi-round encryption" << std::endl;
	std::cout << "4. Back" << std::endl;
	std::cout << "*****************************************************" << std::endl;

	transition();
}

void Menu::lvlTwoDecryption()
{
	state = "lvlTwoDecryption";
	transitions.clear(); // Clear previous choices before adding new ones
	transitions.push_back(&Menu::setStr);
	transitions.push_back(&Menu::setTotalRounds);
	transitions.push_back(&Menu::instantiateDecoder);
	transitions.push_back(&Menu::lvlOne);


	std::cout << "****************************************************************************" << std::endl;
	std::cout << "Menu - Lvl 2 : Decryption" << std::endl;
	std::cout << "1. Enter a message" << std::endl;
	std::cout << "2. Enter the round number" << std::endl;
	std::cout << "3. For each round, print the grid and the corresponding decoded message. " << std::endl;
	std::cout << "4. Back" << std::endl;
	std::cout << "****************************************************************************" << std::endl;

	transition();
}

void Menu::lvlThreeSingleEncryption()
{
	if (str.empty())
	{
		std::cout << "Cannot proceed with empty message. Returing to previous state." << std::endl;
		lvlTwoEncryption();
	}
	else
	{
		state = "lvlThreeSingleEncryption";
		transitions.clear(); // Clear previous choices before adding new ones
		transitions.push_back(&Menu::setGridSize);
		transitions.push_back(&Menu::autoGridSize);
		transitions.push_back(&Menu::instantiateEncoder);
		transitions.push_back(&Menu::lvlTwoEncryption);

		totalRounds = 1;
		std::cout << "*****************************************************" << std::endl;
		std::cout << "Menu - Lvl 3 : Encryption" << std::endl;
		std::cout << "1. Enter a grid size" << std::endl;
		std::cout << "2. Automatic grid size" << std::endl;
		std::cout << "3. Print the grid and the encoded message" << std::endl;
		std::cout << "4. Back" << std::endl;
		std::cout << "*****************************************************" << std::endl;

		transition();
	}
}

void Menu::lvlThreeMultiEncryption()
{
	if (str.empty())
	{
		std::cout << "Cannot proceed with empty message. Returing to previous state." << std::endl;
		lvlTwoEncryption();
	}
	else
	{
		state = "lvlThreeMultiEncryption";
		transitions.clear(); // Clear previous choices before adding new ones
		transitions.push_back(&Menu::setTotalRounds);
		transitions.push_back(&Menu::instantiateEncoder);
		transitions.push_back(&Menu::lvlTwoEncryption);

		std::cout << "****************************************************************************" << std::endl;
		std::cout << "Menu - Lvl 3 : Encryption" << std::endl;
		std::cout << "1. Enter the round number" << std::endl;
		std::cout << "2. For each round, print the grid and the corresponding encoded message" << std::endl;
		std::cout << "3. Back" << std::endl;
		std::cout << "****************************************************************************" << std::endl;

		transition();
	}
}

void Menu::instantiateDecoder()
{
	if (str.size() <= 0)
	{
		std::cout << "Message must be non empty."; // TODO: Move this to the decoder constructor.
	}
	else
	{ 
		try
		{
			Decoder d(str, totalRounds);
			decoder = d;
		}
		catch (std::invalid_argument& error)
		{
			std::cout << "Error: " << error.what() << std::endl;
		}
	}
	displayCurrentStateMenu();

}

void Menu::instantiateEncoder()
{
	try
	{
		if (gridSize == -1) // Automatically choose grid size.
		{
			Encoder e(str, totalRounds);
			encoder = e;
		}
		else // Manually choose grid size.
		{
			Encoder e(str, totalRounds, gridSize);
		}
	}
	catch (std::invalid_argument& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	displayCurrentStateMenu();

}

void Menu::setStr()
{
    std::string s;
    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, s); // Reads the whole line, including spaces

        if (s.empty()) {
            std::cout << "Message cannot be empty. Please try again." << std::endl;
            continue;
        }

        // Check for non-ASCII characters
        bool isAscii = true;
        for (char c : s) {
            if (static_cast<unsigned char>(c) > 127) {
                isAscii = false;
                break;
            }
        }
        if (!isAscii) {
            std::cout << "Message contains non-ASCII characters. Please enter only ASCII characters." << std::endl;
            continue;
        }

        str = s;
        break;
    }
    displayCurrentStateMenu();
}

void Menu::setTotalRounds()
{
	int r;
	while (true) {
		std::cout << "Enter num rounds: ";
		std::cin >> r;

		if (std::cin.fail() || r <= 0) {
			std::cout << "Invalid input. Please enter an integer larger than 1." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any extra input
			break;
		}
	}
	totalRounds = r;
	displayCurrentStateMenu();
}

void Menu::setGridSize()
{
	int g;
	while (true) {
		std::cout << "Enter grid size: ";
		std::cin >> g;

		if (std::cin.fail()) {
			std::cout << "Invalid input. Please ensure an integer is being inputted." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear any extra input
			break;
		}
	}
	gridSize = g;
	displayCurrentStateMenu();
}

void Menu::autoGridSize()
{
	gridSize = -1;
	std::cout << "Grid size will be automatically chosen." << std::endl;
	displayCurrentStateMenu();
}

void Menu::displayCurrentStateMenu()
{
	if (state == "lvlOne") lvlOne();
	else if (state == "lvlTwoEncryption") lvlTwoEncryption();
	else if (state == "lvlTwoDecryption") lvlTwoDecryption();
	else if (state == "lvlThreeSingleEncryption") lvlThreeSingleEncryption();
	else if (state == "lvlThreeMultiEncryption") lvlThreeMultiEncryption();
}
