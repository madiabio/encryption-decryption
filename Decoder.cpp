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

	// catch if encrypted msg length is not an odd perfect square
	int len = static_cast<int>(encryptedMsg.length());
	int root = static_cast<int>(std::sqrt(len));
	if (root * root != len || root % 2 == 0) {
		throw std::invalid_argument("Encrypted message length must be an odd perfect square.");
	}

	// This should handle any other problems with the input.
	setGridSize(static_cast<int>(std::sqrt(encryptedMsg.length())));
	setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize)));
	makeGrid();

	decrypt();
}

void Decoder::makeGrid()
{
	// Fill the grid with the encrypted message.
	int i = 0;
	for (int j = 0; j < gridSize; ++j)
	{
		for (int k = 0; k < gridSize; ++k)
		{
			grid[k][j] = encryptedMsg[i];
			++i;
		}
	}
}


void Decoder::decode()
{
	// if no fullstop, then the unencrypted message ends in the middle of the grid.
    bool fullstop = false;
    int stop_row = gridSize / 2;
	int stop_col = gridSize / 2;

	// if in last round of decryption, look for fullstop.
	if (completedRounds == totalRounds-1)
	{
		// inspect for fullstop.
		for (auto& ch : encryptedMsg) 
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
			for (int i = 0; i < gridSize; ++i)
			{
				for (int j = 0; j < gridSize; ++j)
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

    while ((i < msg.length() || !fullstop_located) && starting_col < (gridSize / 2)) {
        int top_row_of_layer = starting_col;
        int current_col = starting_col;

		// TODO: refactor this to the MessageHandler class and replace the inner function that happens inside of the diagonal code with a function call so it can be overridden
		// by each child class.

        // up & right diagonal
        for (row = gridSize / 2; row > top_row_of_layer; --row) {
			if (grid[row][current_col] == '.' && fullstop) { setMsg(decryptedMsg); return; }
			decryptedMsg += grid[row][current_col];
            current_col++;
        }

        // down & right diagonal
        for (row = top_row_of_layer; row < gridSize / 2; ++row) {
			if (grid[row][current_col] == '.' && fullstop) { setMsg(decryptedMsg); return; }
			decryptedMsg += grid[row][current_col];
            current_col++;
        }

        int bottom_row_of_layer = gridSize - top_row_of_layer;

        // down & left diagonal
        for (row = gridSize / 2; row < bottom_row_of_layer - 1; ++row) {
			if (grid[row][current_col] == '.' && fullstop) { setMsg(decryptedMsg); return; }
			decryptedMsg += grid[row][current_col];
			current_col--;
        }

        // up & left diagonal
        for (row = bottom_row_of_layer - 1; row > gridSize / 2; --row) {
			if (grid[row][current_col] == '.' && fullstop) { setMsg(decryptedMsg); return; }
			decryptedMsg += grid[row][current_col];
            current_col--;
        }

        starting_col++;
        if (starting_col == gridSize / 2) {
			if (grid[row][current_col+1] == '.' && fullstop) { setMsg(decryptedMsg); return; }
			decryptedMsg += grid[row][current_col+1];
        }
    }
	msg = decryptedMsg;
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



void Decoder::decrypt()
{
	// Make grid & encode based off of current params
	makeGrid();
	decode();
	setCompletedRounds(1);

	// If there's more rounds to do, handle it here.
	while (completedRounds < totalRounds)
	{
		if ( completedRounds == totalRounds ) // if its the last round, do special stuff.
		{
			// check if fullstop is present, remove all chars after the fullstop if there is one.
			size_t pos = msg.find('.');
			if (pos != std::string::npos) {
				msg.erase(pos + 1); // Keeps the fullstop, removes everything after
			}
			else
			{
				// otherwise, just proceed as normal.
				int x;
			}

		}
		else // otherwise, keep doing it like this.
		{
			// 1) check if lenght of last round's output is a perfect square of an odd number.
				// if not, remove characters until it is one.

			setEncryptedMsg(msg); // Set the new encrypted message to be the output of the previous decryption.
			setGridSize(minDiamondGridSize(msg.size())); // update the grid size for the new string length
			setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize))); // set the grid
			makeGrid(); // make the grid again
		}

		decode(); // update the encrypted msg with the new encrypted msg.
		setCompletedRounds(completedRounds + 1); // finish the round
	}

}
