#pragma once  
#include "MessageHandler.h"  
/// <summary>  
/// Tools to decode an encrypted message.  
/// </summary>  
class Decoder : public MessageHandler  
{  
private:  
	/// <summary>  
	/// Puts the encrypted message in its grid format.  
	/// </summary>  
	void makeGrid() override;  

	/// <summary>
	/// Sets the size of the grid if it is valid.
	/// </summary>
	/// <param name="g">New grid size</param>
	void setGridSize(int g) override;

	/// <summary>  
	/// Unravels the grid in the diamond pattern and updates msg.
	/// </summary>  
	void decode();

	/// <summary>
	/// returns true if n is a perfect square of an odd number.
	/// </summary>
	/// <param name="n">Int to check if it is a perfect square of an odd number.</param>
	static bool isPerfectSquareOfOddNumber(int n);

	/// <summary>
	/// Removes characters from string str until the length is a perfect square of an odd number.
	/// </summary>
	/// <param name="str">String to remove chars from</param>
	static void trimToPerfectSquareOfOddNumberLength(std::string& str);

public:  
	/// <summary>  
	/// Default constructor  
	/// </summary>  
	Decoder() : MessageHandler() {}  

	/// <summary>
	/// Sets decoder to just do 1 round of decryption using just the encryptedMsg string.
	/// </summary>
	/// <param name="e">Encrypted message</param>  
	Decoder(const std::string& e);

	/// <summary>
	/// Sets decoder with just encryption rounds. Encrypted string must be set before running encrypt.
	/// </summary>
	/// <param name="r">Number of decryption rounds to perform.</param>  
	Decoder(int r) : Decoder("") { setTotalRounds(r); }

	/// <summary>  
	/// Constructor that takes in an encrypted message and the number of encrypted rounds performed on it.
	/// </summary>  
	/// <param name="e">Encrypted message</param>  
	/// <param name="r">Number of decryption rounds to perform.</param>  
	Decoder(const std::string& e, int r);  

	/// <summary>
	/// Decrypts the encrypted message in totalRounds rounds.
	/// </summary>
	void decrypt();

	/// <summary>
	/// Sets the encrypted message.
	/// </summary>
	/// <param name="e">Encrypted message to set.</param>
	void setEncryptedMsg(const std::string& e) override;

	/// <summary>
	/// Automatically sets the grid size to the square root of the length of the encrypted message string.
	/// </summary>
	void setGridSize() override;
};
