#include "pch.h"
#include "Decoder.h"
#include <string>
#include <cmath>

Decoder::Decoder(const std::string& e, int r)
{
	setMsg("");
	setEncryptedMsg(e);
	setTotalRounds(r);
	setCompletedRounds(0);
	// This should handle any other problems with the input.
	setGridSize(static_cast<int>(std::sqrt(getEncryptedMsg().length())));
	setGrid(std::vector<std::vector<char>>(getGridSize(), std::vector<char>(getGridSize())));
	makeGrid();
}

void Decoder::setEncryptedMsg(const std::string& e)
{
	if (e.empty()) throw std::invalid_argument("Encrypted message cannot be empty.");
	if (!isPerfectSquareOfOddNumber(e.length())) throw std::invalid_argument("Encrypted message must be length such that it is the perfect square of an odd number.");
	
	// Check for more than one fullstop
	if (std::count(e.begin(), e.end(), '.') > 1)
		throw std::invalid_argument("Only one fullstop can be in the encrypted message.");

	// Check that all characters are A-Z, a-z, or '.'
	for (char c : e) {
		if (c != '.' && !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
			throw std::invalid_argument("Encrypted message can only contain letters A-Z, a-z, and at most one fullstop.");
		}
	}

	encryptedMsg = e;
}

void Decoder::makeGrid()
{
	// Fill the grid with the encrypted message.
	int i = 0;
	for (int j = 0; j < getGridSize(); ++j)
	{
		for (int k = 0; k < getGridSize(); ++k)
		{
			if (i < getEncryptedMsg().size()) grid[k][j] = getEncryptedMsg()[i];
			else grid[k][j] = getRandomLetter();
			++i;
		}
	}
}

void Decoder::decode()
{
	// if no fullstop, then the unencrypted message ends in the middle of the grid.
    bool fullstop = false;
    int stop_row = getGridSize() / 2;
	int stop_col = getGridSize() / 2;

	// if in last round of decryption, look for fullstop.
	if (getCompletedRounds() == getTotalRounds()-1)
	{
		// inspect for fullstop.
		for (auto& ch : getEncryptedMsg())
		{
			if (ch == '.') 
			{ 
				fullstop = true; 
				break;
			}
		}

		// find coordinate of fullstop. (can probs remove this actually)
		if (fullstop)
		{
			bool found = false;
			for (int i = 0; i < getGridSize(); ++i)
			{
				for (int j = 0; j < getGridSize(); ++j)
				{
					if (grid[i][j] == '.')
					{
						stop_row = i;
						stop_col = j;
						found = true;
						break;
					}
				}
				if (found) { break;} // break once location of fullstop is found.
			}
		}
	}

	// FROM ENCODER:
    int i = 0;
    int starting_col = 0;
    bool fullstop_located = false;
    std::string decryptedMsg;
	int row;

    while ((i < getMsg().length() || !fullstop_located) && starting_col < (getGridSize() / 2)) {
        int top_row_of_layer = starting_col;
        int current_col = starting_col;

		// TODO: refactor this to the MessageHandler class and replace the inner function that happens inside of the diagonal code with a function call so it can be overridden
		// by each child class.

        // up & right diagonal
        for (row = getGridSize() / 2; row > top_row_of_layer; --row) {
			if (grid[row][current_col] == '.' && fullstop) { setMsg(decryptedMsg); return; }
			decryptedMsg += grid[row][current_col];
            current_col++;
        }

        // down & right diagonal
        for (row = top_row_of_layer; row < getGridSize() / 2; ++row) {
			if (grid[row][current_col] == '.' && fullstop) { setMsg(decryptedMsg); return; }
			decryptedMsg += grid[row][current_col];
            current_col++;
        }

        int bottom_row_of_layer = getGridSize() - top_row_of_layer;

        // down & left diagonal
        for (row = getGridSize() / 2; row < bottom_row_of_layer - 1; ++row) {
			if (grid[row][current_col] == '.' && fullstop) { setMsg(decryptedMsg); return; }
				decryptedMsg += grid[row][current_col];
			current_col--;
        }

        // up & left diagonal
        for (row = bottom_row_of_layer - 1; row > getGridSize() / 2; --row) {
			if (grid[row][current_col] == '.' && fullstop) { setMsg(decryptedMsg); return; }
				decryptedMsg += grid[row][current_col];
            current_col--;
        }

        starting_col++;
        if (starting_col == getGridSize() / 2) {
			if (grid[row][current_col+1] == '.' && fullstop) { setMsg(decryptedMsg); return; }
			decryptedMsg += grid[row][current_col+1];
        }
    }
	setMsg(decryptedMsg);
}


void Decoder::trimToPerfectSquareOfOddNumberLength(std::string& str)
{
	size_t len = str.length();
	int n = static_cast<int>(std::sqrt(len));

	// Ensure n is odd and n*n <= len
	if (n % 2 == 0) --n;
	while (n > 0 && n * n > static_cast<int>(len)) {
		n -= 2;
	}

	if (n <= 0) {
		throw std::invalid_argument("No valid perfect square of odd number length");  // No valid odd perfect square
	}

	str.erase(n * n); // Trim to the largest odd perfect square length
}

bool Decoder::isPerfectSquareOfOddNumber(int n)
{
	if (n <= 0) return false;

	float root_f = std::sqrt(static_cast<float>(n));
	int root = static_cast<int>(root_f);

	// Check if root is an integer and odd, and root*root == n
	return (root_f == root) && (root % 2 == 1) && (root * root == n);
}



void Decoder::setGridSize(int g)
{
	if (g <= 0) throw std::invalid_argument("Grid size must be greater than zero.");
	if (g % 2 == 0) throw std::invalid_argument("Grid size must be an odd number.");
	if (g < sqrt(getEncryptedMsg().length())) throw std::invalid_argument("Grid size too small for encrypted message length.");
	gridSize = g;
}

void Decoder::decrypt()
{
	// Make grid & encode based off of current params

	setEncryptedMsg(getEncryptedMsg()); // verify the encryptedMsg is ok.
	setGridSize(getGridSize()); // verify gridsize is ok.
	makeGrid();
	decode();
	setCompletedRounds(1);
	printRoundInfo("Decrypted", getMsg());

	// If there's more rounds to do, handle it here.
	while (getCompletedRounds() < getTotalRounds())
	{
		if (!isPerfectSquareOfOddNumber(getMsg().length())) trimToPerfectSquareOfOddNumberLength(msg); // Trim to the correct length if necessary
		setEncryptedMsg(getMsg()); // Set the new encrypted message to be the output of the previous decryption.

		setGridSize(sqrt(getEncryptedMsg().length())); // update the grid size

		setGrid(std::vector<std::vector<char>>(getGridSize(), std::vector<char>(getGridSize()))); // set the grid
		makeGrid(); // make the grid again

		decode(); // update the encrypted getMsg() with the new encrypted getMsg().
		setCompletedRounds(getCompletedRounds() + 1); // finish the round
		printRoundInfo("Decrypted", getMsg());
	}

}
