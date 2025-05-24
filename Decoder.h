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
	/// Sets the size of the grid. This function overrides a virtual function from a base class to
	/// handle the square root of the length of the encrypted message.
	/// </summary>
	void setGridSize(int g) override;

	/// <summary>  
	/// Unravels the grid in the diamond pattern and updates msg.
	/// </summary>  
	void decode();

	/// <summary>
	/// returns true if n is a perfetc square of an odd number.
	/// </summary>
	/// <param name="n">Int to check if it is a perfect square of an odd number.</param>
	bool isPerfectSquareOfOddNumber(int n);

	/// <summary>
	/// Removes characters from string str until the length is a perfect square of an odd number.
	/// </summary>
	/// <param name="str">String to remove chars from</param>
	void trimToPerfectSquareOfOddNumberLength(std::string& str);

public:  
	/// <summary>  
	/// Default constructor  
	/// </summary>  
	Decoder() : MessageHandler() {}  

	/// <summary>
	/// Sets decoder to automatically just do 1 round of encryption using just the error string.
	/// </summary>
	Decoder(const std::string& e) : MessageHandler("", "", 1, 1) {setEncryptedMsg(e); }

	/// <summary>
	/// Sets decoder with just encryption rounds. Encrypted string must be set before running encrypt.
	/// </summary>
	Decoder(int r) : MessageHandler("aaabbbccc", "", r) {}

	/// <summary>  
	/// Constructor that takes in an encrypted message and the number of encrypted rounds performed on it.  
	/// </summary>  
	/// <param name="e">Encrypted message</param>  
	/// <param name="r">Number of decryption rounds to perform.</param>  
	Decoder(const std::string& e, int r);  

	/// <summary>
	/// Decrypts the encrypted message based upon how many decryption rounds were given in the constructor.
	/// </summary>
	void decrypt();

	void setEncryptedMsg(const std::string& e) override;
};
