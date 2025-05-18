/// <summary>
/// Base class for encoding and decoding messages.
/// Handles member functions that will be shared by derived classes.
/// <\summary>
#include "pch.h"
#include "MessageHandler.h"
#include <string>

MessageHandler::MessageHandler() : msg(""), encryptedMsg(""), gridSize(0), grid(gridSize, std::vector<char>(gridSize)), totalRounds(0), roundsCompleted(0) {}
MessageHandler::MessageHandler(const std::string& m, const std::string& e, int r) : msg(m), encryptedMsg(e), totalRounds(r), gridSize(0), roundsCompleted(0)
{
	if (r < 0) throw std::invalid_argument("Number of rounds must be greater than or equal to zero.");
	// TODO: handle automatic grid sizing
}

MessageHandler::MessageHandler(const std::string& m, const std::string& e, int r, int g) : msg(m), encryptedMsg(e), totalRounds(r), gridSize(g), grid(gridSize, std::vector<char>(gridSize)), roundsCompleted(0)
{
	if (r < 0) throw std::invalid_argument("Number of rounds must be greater than or equal to zero.");
	if (g < 0) throw std::invalid_argument("Grid size must be greater than or equal to zero.");
	// TODO: check grid sizing is proper.

}

void MessageHandler::makeGrid()
{
	if (gridSize == 0)
	{
		std::cout << "";
	}
	else
	{
		int idx = 0;
		for (int col = 0; col < gridSize; ++col) {
			for (int row = 0; row < gridSize; ++row) {
				if (idx < this->encryptedMsg.size()) {
					grid[row][col] = this->encryptedMsg[idx++];
				}
				else {
					grid[row][col] = ' '; // or any placeholder for unused cells
				}
			}
		}
	}
}

void MessageHandler::printGrid() const
{
	for (int row = 0; row < gridSize; ++row) {
		for (int col = 0; col < gridSize; ++col) {
			std::cout << grid[row][col];
			if (col < gridSize - 1)
				std::cout << ' '; // Add space between columns
		}
		std::cout << '\n'; // Newline after each row
	}
}
