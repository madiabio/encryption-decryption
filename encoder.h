/// Header file for the encoder class.
#pragma once
#include "MessageHandler.h"
#include <vector>
/// <summary>
/// Class with tools to encrypt a message using the encryption algorithm.
/// </summary>
class Encoder : public MessageHandler
{
private:
    /// <summary>
    /// Sets the encrypted message. Same as base class but moved to private.
    /// </summary>
    /// <param name="e">The encrypted message to set.</param>
    using MessageHandler::setEncryptedMsg;

    static std::string Encoder::removeWhitespace(std::string str);

protected:
    // These are here so they can be inherited by the test class.
    // TODO: once 'encrypt' is made, change the tests to just look at getGrid()

    /// <summary>
    /// Gets a random upper case letter between A-Z.
    /// </summary>
    /// <returns>Returns a random upper case letter.</returns>
    virtual char getRandomLetter();
    /// <summary>

    /// Creates or initializes a grid structure. Overrides a virtual function from a base class.
    /// This method differs from the base class by first initializing the grid using random letters,
    /// then filling it with the encrypted message.
    /// It can only be called after the encrypted message is complete.
    /// </summary>
    void makeGrid() override;

public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Encoder() : MessageHandler() {}

    /// <summary>
    /// Constructor that takes in an unencrypted message, the number of desired encryption rounds, and the grid size.
    /// To be used with automatic grid sizing.
    /// Handles if a message has whitespace or needs to have a fullstop appended.
    /// </summary>
    /// <param name="m">Unencryped message</param>
    /// <param name="r">Number of encryption rounds</param> 
    Encoder(const std::string& m, int r) : MessageHandler(removeWhitespace(m), "", r) { makeGrid(); }


    /// <summary>
    /// Constructor that takes in an unencrypted message, the number of desired encryption rounds, and the grid size.
    /// To be used with manual grid sizing.
    /// Handles if a message has whitespace or needs to have a fullstop appended.
    /// </summary>
    /// <param name="m">Unencryped message</param>
    /// <param name="r">Number of encryption rounds</param> 
    /// <param name="g">Size of grid</param>
    Encoder(const std::string& m, int r, int g) : MessageHandler(removeWhitespace(m), "", r, g) { makeGrid(); }

    /// <summary>
    /// Encodes the message using the encryption algorithm.
    /// </summary>
    void encode();
    
};


