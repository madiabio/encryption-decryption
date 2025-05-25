#pragma once
#include <string>
#include <vector>
class Menu final
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
	/// Prompts user to update the string (message to encrypt/decrypt) and saves it to the encoder/decoder depending on the state.
	/// </summary>
	void updateMessage();

	/// <summary>
	/// Prompts user to update the number of decryption/encryption rounds & saves it to the encoder/decoder depending on the state.
	/// </summary>
	void updateTotalRounds();

	/// <summary>
	/// Prompts the user to update the gridSize saved to the encoder/decoder according to the state.
	/// </summary>
	void updateGridSize();

	/// <summary>
	/// Sets the grid size to -1 so when the encoder is instantiated the control will flow to auto grid size option.
	/// </summary>
	void autoGridSize();

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
	/// Sets string
	/// </summary>
	/// <param name="s">New string to set</param>
	void setStr(std::string s) { str = s; }

	/// <summary>
	/// Sets the state
	/// </summary>
	/// <param name="newState">New state to set</param>
	void setState(std::string newState) { state = newState; }

	/// <summary>
	/// Sets the previous state
	/// </summary>
	/// <param name="newPrevState">New previous state to set.</param>
	void setPrevState(std::string newPrevState) { prevState = newPrevState; }

	/// <summary>
	/// Sets the gridSize member variable.
	/// </summary>
	/// <param name="g">New gridSize to set.</param>
	void setGridSize(int g) { gridSize = g; }

	/// <summary>
	/// Sets the total rounds member variable.
	/// </summary>
	/// <param name="r">New totalRounds value</param>
	void setTotalRounds(int r) { totalRounds = r; }

	/// <summary>
	/// Quits the program
	/// </summary>
	void quit();

	/// <summary>
	/// Gets the current state
	/// </summary>
	/// <returns>Current state</returns>
	std::string getState() const { return state; }

	/// <summary>
	/// Gets the previous state
	/// </summary>
	/// <returns>Previous state</returns>
	std::string getPrevState() const { return prevState; }

	/// <summary>
	/// Gets grid size
	/// </summary>
	/// <returns>gridSize</returns>
	int getGridSize() const { return gridSize; }

	/// <summary>
	/// Gets total rounds
	/// </summary>
	/// <returns>totalRounds</returns>
	int getTotalRounds() const { return totalRounds; }

	/// <summary>
	/// Gets str
	/// </summary>
	/// <returns>str</returns>
	std::string getStr() const { return str; }

	/// <summary>
	/// Gets the decoder
	/// </summary>
	/// <returns>The Decoder d</returns>
	Decoder getDecoder() const { return d; }

	/// <summary>
	/// Gets the encoder
	/// </summary>
	/// <returns>The Encoder e</returns>
	Encoder getEncoder() const { return e; }

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