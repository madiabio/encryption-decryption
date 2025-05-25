/// Header file for the encoder class.
#pragma once
#include "MessageHandler.h"
#include <vector>
#include <string>

/// <summary>
/// Class with tools to encrypt a message using the encryption algorithm.
/// </summary>
class Encoder final: public MessageHandler
{
private:

    /// <summary>
    /// Creates or initializes a grid structure. Overrides a virtual function from a base class.
    /// This method differs from the base class by first initializing the grid using random letters,
    /// then filling it with the encrypted message.
    /// It can only be called after the encrypted message is complete.
    /// </summary>
    void makeGrid() override;

    /// <summary>
    /// Collapses the grid into an encrypted message string.
    /// </summary>
    void encode();

public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    Encoder() : MessageHandler() {}

    /// <summary>
    /// Constructor that takes in a message and nothing else. 
    /// Sets number of encryption rounds to 1 by default.
    /// Automatic grid size.
    /// </summary>
    /// <param name="m"> Message </param>
    Encoder(const std::string& m) : MessageHandler("", "", 1) { setMsg(removeWhitespace(m)); }

    /// <summary>
    /// Constructor that takes in a grid size and nothing else.
    /// Sets number of encryption rounds to 1 by default.
    /// </summary>
    /// <param name="g"></param>
    Encoder(int g) : MessageHandler("", "", 1) { setGridSize(g); }

    /// <summary>
    /// Constructor that takes in an unencrypted message, the number of desired encryption rounds, and the grid size.
    /// To be used with automatic grid sizing.
    /// Handles if a message has whitespace or needs to have a fullstop appended.
    /// Automatically encrypts the message based upon the number of rounds.
    /// </summary>
    /// <param name="m">Unencryped message</param>
    /// <param name="r">Number of encryption rounds</param> 
    Encoder(const std::string& m, int r);

    /// <summary>
    /// Constructor that takes in an unencrypted message, the number of desired encryption rounds, and the grid size.
    /// To be used with manual grid sizing.
    /// Handles if a message has whitespace or needs to have a fullstop appended.
    /// Automatically encrypts the message based upon the number of rounds.
    /// </summary>
    /// <param name="m">Unencryped message</param>
    /// <param name="r">Number of encryption rounds</param> 
    /// <param name="g">Size of grid</param>
    Encoder(const std::string& m, int r, int g);

    /// <summary>
    /// Performs encrpytion for totalRounds rounds. Updates the encryptedMsg member.
    /// </summary>
    void encrypt();

    /// <summary>
    /// Sets the grid size.
    /// </summary>
    /// <param name="g">New grid size.</param>
    void setGridSize(int g) override;

    /// <summary>
    /// Automatically sets the grid size based upon the unencrypted message.
    /// </summary>
    void setGridSize() override;

    /// <summary>
    /// Sets the message
    /// </summary>
    /// <param name="m">New msg string</param>
    void setMsg(const std::string& m) override;
};


