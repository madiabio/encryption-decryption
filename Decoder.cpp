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
	// Access the grid member variable directly or via setGrid/getGrid as needed
	for (int diag = 0; diag <= 2 * (n - 1); ++diag) {
		for (int row = 0; row < n; ++row) {
			int col = diag - row;
			if (col >= 0 && col < n && idx < encryptedMsg.length()) {
				grid[row][col] = encryptedMsg[idx++];
			}
		}
	}
}

