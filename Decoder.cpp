#include "pch.h"
#include "Decoder.h"
#include <string>
#include <cmath>

Decoder::Decoder(const std::string& e, int r) : MessageHandler("", e, r)
{
	// catch if encrypted msg length is not an odd perfect square
	int len = static_cast<int>(encryptedMsg.length());
	int root = static_cast<int>(std::sqrt(len));
	if (root * root != len || root % 2 == 0) {
		throw std::invalid_argument("Encrypted message length must be an odd perfect square.");
	}

	// This should handle any other problems with the input.
	setGridSize(root);
	setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize)));

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
			if (i == (encryptedMsg.length())) { return; } // if we reach the end of the message, break out of the loop.
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
			if (grid[row][current_col] == '.' && fullstop) { break; }
			decryptedMsg += grid[row][current_col];
            current_col++;
        }

        // down & right diagonal
        for (row = top_row_of_layer; row < gridSize / 2; ++row) {
			if (grid[row][current_col] == '.' && fullstop) { break; }
			decryptedMsg += grid[row][current_col];
            current_col++;
        }

        int bottom_row_of_layer = gridSize - top_row_of_layer;

        // down & left diagonal
        for (row = gridSize / 2; row < bottom_row_of_layer - 1; ++row) {
			if (grid[row][current_col] == '.' && fullstop) { break; }
			decryptedMsg += grid[row][current_col];
			current_col--;
        }

        // up & left diagonal
        for (row = bottom_row_of_layer - 1; row > gridSize / 2; --row) {
			if (grid[row][current_col] == '.' && fullstop) { break; }
			decryptedMsg += grid[row][current_col];
            current_col--;
        }

        starting_col++;
        if (starting_col == gridSize / 2) {
			if (grid[row][current_col+1] == '.' && fullstop) { break; }
			decryptedMsg += grid[row][current_col+1];
        }
    }
	setMsg(decryptedMsg);
}

void Decoder::decrypt()
{
	if (totalRounds == 1)
	{
		// Make grid & encode based off of current params
		makeGrid();
		decode();
		setCompletedRounds(1);
	}
	else
	{
		for (int round = 0; round < totalRounds; ++round)
		{
			makeGrid(); // make the grid for the current round.
			setGridSize(static_cast<int>(std::sqrt(encryptedMsg.length()))); // update the grid size for the new string length
			setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize))); // set the grid
			decode(); // update the encrypted msg with the new encrypted msg.
			setCompletedRounds(round); // finish the round
			encryptedMsg = msg; // update the encrypted msg to be the previously decoded msg.
		}
	}
}

void Decoder::setGridSize(int g)
{
	if (g <= 0) throw std::invalid_argument("Grid size must be greater than zero.");
	if (g % 2 == 0) throw std::invalid_argument("Grid size must be a perfect root of an odd number.");
	if (g < std::sqrt(encryptedMsg.length())) throw std::invalid_argument("Grid size too small.");
	gridSize = g;
}