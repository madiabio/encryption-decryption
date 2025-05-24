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
	/// Unravels the grid in the diamond pattern and updates msg.
	/// </summary>  
	void decode();

public:  

	/// <summary>
	/// Removes characters from string str until the length is a perfect square of an odd number.
	/// </summary>
	/// <param name="str">String to remove chars from</param>
	void trimToPerfectSquareOfOddNumberLength(std::string& str);



	/// <summary>  
	/// Default constructor  
	/// </summary>  
	Decoder() : MessageHandler() {}  

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
};
