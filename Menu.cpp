#include "pch.h"
#include "Menu.h"
#include "Encoder.h"
#include "Decoder.h"
#include <iostream>
Menu::Menu() : str(""), gridSize(-2), totalRounds(1), state("lvlOne")
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

	Encoder e;
	encoder = e;

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
		std::cout << "Error: Cannot proceed with empty message. Returing to previous state." << std::endl;
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
		std::cout << "Error: Cannot proceed with empty message. Returing to previous state." << std::endl;
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
	try
	{
		Decoder d(str, totalRounds);
		d.decrypt();
	}
	catch (std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
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
			e.encrypt();
		}
		else if (gridSize > 0) // Manually choose grid size (total rounds = 1)
		{
			Encoder e(str, 1, gridSize);
			e.encrypt();
		}
		else if (gridSize == -2)
		{
			throw std::invalid_argument("Cannot proceed with unset grid choice.");
		}
	}
	catch (std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	displayCurrentStateMenu();

}

void Menu::setStr()
{
	std::string s;
	std::cout << "Enter message: ";
	std::getline(std::cin, s);
	try
	{
		if (s.empty())
		{
			throw std::invalid_argument("Message cannot be empty.");
		}
		if (state == "lvlTwoEncryption")
		{
			Encoder e(s);
		}
		else if (state == "lvlTwoDecryption")
		{
			Decoder d(s, totalRounds);

		}
		str = s;
	}
	catch (std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	displayCurrentStateMenu();
}

void Menu::setTotalRounds()
{
	int r;
	std::string line;
	std::cout << "Enter num rounds: ";
	std::getline(std::cin, line);
	try 
	{
		if (line.empty())
		{
			throw std::invalid_argument("Number of rounds cannot be empty.");
		}

		r = std::stoi(line);
		if (state == "lvlThreeMultiEncryption")
		{
			Encoder e("test", r);
		}
		else if (state == "lvlTwoDecryption")
		{
			Decoder d(r);
		}
		totalRounds = r;
	}
	catch (std::exception& error) 
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	displayCurrentStateMenu();
}

void Menu::setGridSize()
{
	int g;
	std::string line;
	std::cout << "Enter grid size: ";
	std::getline(std::cin, line);

	try 
	{
		if (line.empty())
		{
			throw std::invalid_argument("Grid size cannot be empty.");
		}

		g = std::stoi(line);
		Encoder e(str, 1, g);
		gridSize = g;
	}
	catch (std::exception& error) {
		std::cout << "Error: " << error.what() << std::endl;
	}
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
