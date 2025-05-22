/// <summary>
/// Base class for encrypting and decrypting messages.
/// Handles members that will be shared by derived classes.
/// <\summary>
#pragma once
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
	/// The number of encryption/decryption rounds that will be done.
	/// </summary>
	int totalRounds;

	/// <summary>
	/// The number of encryption/decryption rounds that have been done so far for the current message.
	/// </summary>
	int completedRounds;

	/// <summary>
	/// 2d grid that is used to create and display the encrypted message
	/// </summary>
	std::vector<std::vector<char>> grid;


	/// <summary>
	/// Returns the number of cells in a diamond for an odd grid size n
	/// </summary>
	/// <param name="n">Odd grid size n</param
	int diamondCellCount(int n);

	/// <summary>
	/// Calculates the minimum grid size required to fit a message in a diamond-shaped grid.
	/// </summary>
	/// <param name="messageLength">The length of the message to be placed in the diamond grid.</param>
	/// <returns>The smallest integer grid size that can accommodate the entire message in a diamond pattern.</returns>
	int minDiamondGridSize(int messageLength);



public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	MessageHandler();

	/// <summary>
	/// Constructor that takes in unencrypted message, encrypted message and number of rounds. 
	/// To be used with automatic grid size setting.
	/// </summary>
	/// <param name="m">Unencryped message</param>
	/// <param name="e">Encrypted message</param> 
	/// <param name="r">Number of rounds</param> 
	/// <param name="g">Size of grid</param>
	MessageHandler(const std::string& m, const std::string& e, int r);
	/// <summary>
	/// Constructor that takes in unencrypted message, encrypted message, number of rounds and grid size. 
	/// To be used with manual grid size setting.
	/// </summary>
	/// <param name="m">Unencryped message</param>
	/// <param name="e">Encrypted message</param> 
	/// <param name="r">Number of rounds</param> 
	/// <param name="g">Size of grid</param>
	MessageHandler(const std::string& m, const std::string& e, int r, int g);

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
	/// Gets the number of encryption rounds required to encrypt or decrypt the unencrypted message.
	/// </summary>
	/// <returns>The number of encrpytion rounds as an int.</returns>
	int getTotalRounds() const { return totalRounds; }

	/// <summary>
	/// Gets the number of rounds that have been completed by the current encryption or decryption process.
	/// </summary>
	/// <returns>The number of encryption or decryption rounds that have been completed as an int.</returns>
	int getCompletedRounds() const { return completedRounds; }

	/// <summary>
	/// Gets the grid size.
	/// </summary>
	/// <returns>The size of the grid as an int.</returns>
	int getGridSize() const { return gridSize ; }

	/// <summary>
	/// Gets the 2d grid as a 2d vector of chars.
	/// </summary>
	/// <returns>The encrypyted message as a 2d vector of chars</returns>
	std::vector<std::vector<char>> getGrid() const{ return grid; }

	/// <summary>
	/// Prints the 2d grid.
	/// </summary>
	void printGrid() const;

	/// <summary>
	/// Puts the encrypted message in its grid format.
	/// </summary>
	virtual void makeGrid();

	/// <summary>
	/// Sets the unencrypted message.
	/// </summary>
	/// <param name="m">Unencrypted message.</param>
	virtual void setMsg(const std::string& m) { msg = m; }

	/// <summary>
	///	Sets the encrypted message.
	/// </summary>
	/// <param name="e">Encrypted message.</param>
	virtual void setEncryptedMsg(const std::string& e) { encryptedMsg = e; }

	/// <summary>
	/// Sets the grid size to the specified value if valid. If new number < 0, throws invalid argument.
	/// </summary>
	/// <param name="g">The new grid size.</param>
	virtual void setGridSize(int g);

	/// <summary>
	/// Sets the total number of rounds if valid. If new number < 0, throws invalid argument.
	/// </summary>
	/// <param name="r">The total number of rounds to set.</param>
	virtual void setTotalRounds(int r) { (r < 0) ? throw std::invalid_argument("Total rounds must be greater than zero.") : totalRounds = r; }

	/// <summary>
	/// Sets the number of completed rounds if valid. If new number < 0, throws invalid argument.
	/// </summary>
	/// <param name="rc">The number of rounds that have been completed.</param>
	virtual void setCompletedRounds(int rc) { (rc < 0) ? throw std::invalid_argument("Number of completed rounds must be greater than zero.") : completedRounds = rc; }
	
	/// <summary>
	/// Sets the grid to a new two-dimensional character array.
	/// </summary>
	/// <param name="newGrid">The new grid to assign, represented as a two-dimensional vector of characters.</param>
	virtual void setGrid(std::vector<std::vector<char>> newGrid);


	/// <summary>
	/// Virtual destructor.
	/// </summary>
	virtual ~MessageHandler() {}

};

