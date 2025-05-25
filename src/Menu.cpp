#include "pch.h"
#include "../include/Menu.h"
#include "../include/Encoder.h"
#include "../include/Decoder.h"
#include <iostream>
Menu::Menu() : str(""), gridSize(-2), totalRounds(1), state("None") {}

void Menu::start()
{
	std::cout << "Welcome to the Encryption/Decryption Menu!" << std::endl;
	lvlOne(); // Start with level one menu
}

void Menu::quit()
{
	std::cout << "Exiting program..." << std::endl;
	exit(0); 
}

void Menu::lvlOne()
{
	setState("lvlOne");
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
	std::string line;
	int input;
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
			if (getPrevState() != getState()) 
			{
				setPrevState(getState()); // Save the current state before transitioning
			}
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
	setState("lvlTwoEncryption");
	transitions.clear(); // Clear previous choices before adding new ones
	transitions.push_back(&Menu::updateMessage);
	transitions.push_back(&Menu::lvlThreeSingleEncryption);
	transitions.push_back(&Menu::lvlThreeMultiEncryption);
	transitions.push_back(&Menu::lvlOne);

	if (getPrevState()!= getState())
	{
		str.clear(); // reset msg if necessary.
	}

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
	setState("lvlTwoDecryption");
	transitions.clear(); // Clear previous choices before adding new ones
	transitions.push_back(&Menu::updateMessage);
	transitions.push_back(&Menu::updateTotalRounds);
	transitions.push_back(&Menu::instantiateDecoder);
	transitions.push_back(&Menu::lvlOne);

	if (getPrevState()!= getState())
	{
		setTotalRounds(0); // reset total rounds if necessary.
		str.clear(); // reset msg if necessary.
	}

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

		setState("lvlThreeSingleEncryption");
		transitions.clear(); // Clear previous choices before adding new ones
		transitions.push_back(&Menu::updateGridSize);
		transitions.push_back(&Menu::autoGridSize);
		transitions.push_back(&Menu::instantiateEncoder);
		transitions.push_back(&Menu::lvlTwoEncryption);

		if (getPrevState()!= getState())
		{
			setTotalRounds(1); // total rounds is always 1 at this state.
			e.setTotalRounds(1); // total rounds is always 1 for this state.
		}	

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

		setState("lvlThreeMultiEncryption");
		transitions.clear(); // Clear previous choices before adding new ones
		transitions.push_back(&Menu::updateTotalRounds);
		transitions.push_back(&Menu::instantiateEncoder);
		transitions.push_back(&Menu::lvlTwoEncryption);

		if (getPrevState()!= getState())
		{
			setTotalRounds(0); // reset total rounds if necessary.
		}

		setGridSize(-1); // automatically choose grid size.
		e.setGridSize(); // automatically choose grid size.

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
		if (getTotalRounds() == 0) throw std::invalid_argument("Cannot decrypt without setting total rounds > 0.");
		d.decrypt();
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	displayCurrentStateMenu();
}

void Menu::instantiateEncoder()
{
	try
	{
		if (getGridSize() >= -1 && getTotalRounds() > 0) e.encrypt(); // Grid size was set. 
		else if (getGridSize() == -2) throw std::invalid_argument("Cannot proceed with unset grid choice."); // Grid size wasn't set
		else if (getTotalRounds() == 0) throw std::invalid_argument("Cannot decrypt without setting total rounds > 0."); // Total rounds not set.
	}
	catch (const std::exception& error) { std::cout << "Error: " << error.what() << std::endl; }
	displayCurrentStateMenu();
}

void Menu::updateMessage()
{
	std::string s;
	std::cout << "Enter message: ";
	std::getline(std::cin, s);
	try
	{
		if (s.empty()) throw std::invalid_argument("Message cannot be empty.");
		if (state == "lvlTwoEncryption") e.setMsg(s); // Check its valid for encoder to construct with this string.
		else if (state == "lvlTwoDecryption") d.setEncryptedMsg(s); // Check its valid for decoder to construct with this string.
		str = s;
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	displayCurrentStateMenu();
}

void Menu::updateTotalRounds()
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
			e.setTotalRounds(r); // Check its valid for encoder to construct with this number of rounds.
		}
		else if (state == "lvlTwoDecryption")
		{
			d.setTotalRounds(r); // Check its valid for decoder to construct with this number of rounds.
		}
		setTotalRounds(r);
	}
	catch (const std::exception& error) 
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	displayCurrentStateMenu();
}

void Menu::updateGridSize()
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
		e.setGridSize(g); // Check its valid for encoder to construct with this size of grid, given the previously inputted message string. (grid size is only ever set for encoder)
		setGridSize(g);
	}
	catch (const std::exception& error) {
		std::cout << "Error: " << error.what() << std::endl;
	}
	displayCurrentStateMenu();
}

void Menu::autoGridSize()
{
	setGridSize(-1);
	std::cout << "Grid size will be automatically chosen." << std::endl;
	e.setGridSize();
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
