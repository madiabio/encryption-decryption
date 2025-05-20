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
	setGridSize(static_cast<int>(std::sqrt(encryptedMsg.length())));
	setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize)));
	makeGrid();
}

void Decoder::makeGrid()
{
	int n = gridSize;
	int idx = 0;
	for (int diag = 0; diag <= 2 * (n - 1); ++diag) {
		for (int row = 0; row < n; ++row) {
			int col = diag - row;
			if (col >= 0 && col < n && idx < encryptedMsg.length()) {
				grid[row][col] = encryptedMsg[idx++];
			}
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
    std::string& decryptedMsg;
	int row;

    while ((i < msg.length() || !fullstop_located) && starting_col < (gridSize / 2)) {
        int top_row_of_layer = starting_col;
        int current_col = starting_col;

        // up & right diagonal
        for (row = gridSize / 2; row > top_row_of_layer; --row) {
            decryptedMsg += grid[row][current_col];
            if (grid[row][current_col] == '.' && fullstop) { break; }
            current_col++;
        }

        // down & right diagonal
        for (row = top_row_of_layer; row < gridSize / 2; ++row) {
            decryptedMsg += grid[row][current_col];
            if (grid[row][current_col] == '.' && fullstop) { break; }
            current_col++;
        }

        int bottom_row_of_layer = gridSize - top_row_of_layer;

        // down & left diagonal
        for (row = gridSize / 2; row < bottom_row_of_layer - 1; ++row) {
			decryptedMsg += grid[row][current_col];
			if (grid[row][current_col] == '.' && fullstop) { break; }
			current_col--;
        }

        // up & left diagonal
        for (row = bottom_row_of_layer - 1; row > gridSize / 2; --row) {
			decryptedMsg += grid[row][current_col];
			if (grid[row][current_col] == '.' && fullstop) { break; }
            current_col--;
        }

        starting_col++;
        if (starting_col == gridSize / 2) {
			decryptedMsg += grid[row][current_col];
			if (grid[row][current_col] == '.' && fullstop) { break; }
        }
    }

}