#pragma once
#include <string>
#include <vector>
class Menu
{
private:

	Encoder e;

	Decoder d;
	
	/// <summary>
	/// Message to either encrypt or decrypt.
	/// </summary>
	std::string str;

	/// <summary>
	/// The size of the grid, if using manual grid sizing.
	/// </summary>
	int gridSize;

	/// <summary>
	/// The number of encryption/decryption rounds to complete.
	/// </summary>
	int totalRounds = 1;

	/// <summary>
	/// The current menu state
	/// </summary>
	std::string state;
	
	/// <summary>
	/// The previous state.
	/// </summary>
	std::string prevState;

	/// <summary>
	/// The choices available from the current menu state.
	/// </summary>
	std::vector<void (Menu::*)()> transitions;

	/// <summary>
	/// The starter menu.
	/// </summary>
	void lvlOne();

	/// <summary>
	/// The menu that shows if '1' is selected at lvl 1.
	/// </summary>
	void lvlTwoEncryption();

	/// <summary>
	/// The menu that shows if '2' is selected at lvl 1.
	/// </summary>
	void lvlTwoDecryption();

	/// <summary>
	/// The menu that shows the signle round encryption options.
	/// </summary>
	void lvlThreeSingleEncryption();

	/// <summary>
	/// The menu that shows the multi round encrpytion options.
	/// </summary>
	void lvlThreeMultiEncryption();

	/// <summary>
	/// Sets the string (message to encrypt/decrypt)
	/// </summary>
	void setStr();

	/// <summary>
	/// Sets the number of decryption/encryption rounds.
	/// </summary>
	void setTotalRounds();
	
	/// <summary>
	/// Instantaites a decoder based upon the totalRounds and the message.
	/// </summary>
	void instantiateDecoder();

	/// <summary>
	/// Instantiates an encoder based upon totalRounds, gridSize and the message.
	/// </summary>
	void instantiateEncoder();

	/// <summary>
	/// Gets the input from a user and makes a choice corresponding to the available choices in the state.
	/// </summary>
	void transition();

	/// <summary>
	/// Shows the menu of the current state.
	/// </summary>
	void displayCurrentStateMenu();

	/// <summary>
	/// Returns to the previous state.
	/// </summary>
	void transitionToPreviousState();

	/// <summary>
	/// Quits the program
	/// </summary>
	void quit();

	/// <summary>
	/// Sets gridSize for when the encoder is instantiated 
	/// </summary>
	void setGridSize();

	/// <summary>
	/// Sets the grid size to -1 so when the encoder is instantiated the control will flow to auto grid size option.
	/// </summary>
	void autoGridSize();
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	Menu();

	/// <summary>
	/// Starts the menu loop.
	/// </summary>
	void start();

	/// <summary>
	/// Default destructor
	/// </summary>
	~Menu() {}
};