/// Header file for the encoder class.
#pragma once
#include "MessageHandler.h"

/// <summary>
/// Class with tools to encrypt a message using the encryption algorithm.
/// </summary>
class Encoder : public MessageHandler
{
protected:

    /// <summary>
    /// Gets a random upper case letter between A-Z.
    /// </summary>
    /// <returns>Returns a random upper case letter.</returns>
    char getRandomLetter();
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Encoder() : MessageHandler() {}

    /// <summary>
    /// Constructor that takes in an unencrypted message, the number of desired encryption rounds, and the grid size.
    /// To be used with automatic grid sizing.
    /// </summary>
    /// <param name="m">Unencryped message</param>
    /// <param name="r">Number of encryption rounds</param> 
    Encoder(const std::string& m, int r) : MessageHandler(m, "", r) {}

    /// <summary>
    /// Constructor that takes in an unencrypted message, the number of desired encryption rounds, and the grid size.
    /// To be used with manual grid sizing.
    /// </summary>
    /// <param name="m">Unencryped message</param>
    /// <param name="r">Number of encryption rounds</param> 
    /// <param name="g">Size of grid</param>
    Encoder(const std::string& m, int r, int g) : MessageHandler(m, "", r, g) {}

    /// <summary>
    /// Encodes the message using the encryption algorithm.
    /// </summary>
    void encode();
};


