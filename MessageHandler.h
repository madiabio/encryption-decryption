/// <summary>
/// Base class for encrypting and decrypting messages.
/// Handles members that will be shared by derived classes.
/// <\summary>
#pragma once
#include <string>
class MessageHandler
{
protected:
	/// <summary>
	/// Unencrypted message.
	/// </summary>
	std::string msg;

	/// <summary>
	/// Encrypted message.
	/// </summary>
	std::string encryptedMsg;

	/// <summary>
	/// Size of the grid that will be used for encrypting and decrypting.
	/// </summary>
	int gridSize;

	/// <summary>
	/// The number of encryption rounds that will be used or were used.
	/// </summary>
	int rounds;

public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	MessageHandler() : msg(""), encryptedMsg(""), gridSize(0), rounds(0) {}

	/// <summary>
	/// Constructor that takes in unencrypted message, encrypted message and number of rounds. 
	/// To be used with automatic grid size setting.
	/// </summary>
	/// <param name="m">Unencryped message</param>
	/// <param name="e">Encrypted message</param> 
	/// <param name="r">Number of rounds</param> 
	/// <param name="g">Size of grid</param>
	MessageHandler(const std::string& m, const std::string& e, int r) : msg(m), encryptedMsg(e), rounds(r), gridSize(0) 
	{
		// TODO: implement functionality for automatic grid size calculation (might need to move this definition to
		// the .cpp file)
	}

	/// <summary>
	/// Constructor that takes in unencrypted message, encrypted message, number of rounds and grid size. 
	/// To be used with manual grid size setting.
	/// </summary>
	/// <param name="m">Unencryped message</param>
	/// <param name="e">Encrypted message</param> 
	/// <param name="r">Number of rounds</param> 
	/// <param name="g">Size of grid</param>
	MessageHandler(const std::string& m, const std::string& e, int r, int g) : msg(m), encryptedMsg(e), rounds(r), gridSize(g) {}

	/// <summary>
	/// Gets the unencrypted message.
	/// </summary>
	/// <returns>The unencrypted message as a std::string.</returns>
	std::string getMsg() const { return msg; }

	/// <summary>
	/// Gets the encrypted message.
	/// </summary>
	/// <returns>The encrypted message as a std::string.</returns>
	std::string getEncryptedMsg() const { return encryptedMsg; }

	/// <summary>
	/// Gets the number of encryption rounds.
	/// </summary>
	/// <returns>The number of encrpytion rounds as an int.</returns>
	int getRounds() const { return rounds; }

	/// <summary>
	/// Gets the grid size.
	/// </summary>
	/// <returns>The size of the grid as an int.</returns>
	int getGridSize() const { return gridSize; }

	/// <summary>
	/// Prints the encrypted message in its grid format.
	/// </summary>
	void printEncryptedMsg() const;

	/// <summary>
	/// Virtual destructor.
	/// </summary>
	virtual ~MessageHandler() {}

};

