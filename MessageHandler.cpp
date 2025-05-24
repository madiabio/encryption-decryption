/// <summary>
/// Base class for encoding and decoding messages.
/// Handles member functions that will be shared by derived classes.
/// <\summary>
#include "pch.h"
#include "MessageHandler.h"
#include <string>

MessageHandler::MessageHandler() : msg(""), encryptedMsg(""), gridSize(1), totalRounds(0), completedRounds(0) {}
MessageHandler::MessageHandler(const std::string& m, const std::string& e, int r) : msg(removeWhitespace(m)), encryptedMsg(e), gridSize(0), completedRounds(0)
{
	setTotalRounds(r);
	setGridSize(minDiamondGridSize(m.size()));
	setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize)));
	makeGrid();
}

MessageHandler::MessageHandler(const std::string& m, const std::string& e, int r, int g) : msg(removeWhitespace(m)), encryptedMsg(e), completedRounds(0)
{
	setTotalRounds(r);
	setGridSize(g);
	setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize)));
}

void MessageHandler::makeGrid()
{
	int idx = 0;
	for (int col = 0; col < gridSize; ++col) {
		for (int row = 0; row < gridSize; ++row) {
			if (idx < this->encryptedMsg.size()) {
				grid[row][col] = this->encryptedMsg[idx++];
			}
			else {
				grid[row][col] = '*';
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

void MessageHandler::setGrid(std::vector<std::vector<char>> newGrid)
{
	grid = newGrid;
}


void MessageHandler::setGridSize(int g) 
{
	if (g <= 0) throw std::invalid_argument("Grid size must be greater than zero.");
	if (g % 2 == 0) throw std::invalid_argument("Grid size must be an odd number.");
	int minSize = minDiamondGridSize(msg.size());
	if (g < minSize) throw std::invalid_argument("Grid size too small.");
	gridSize = g;

}

int MessageHandler::diamondCellCount(int n) {
	if (n <= 0 || n % 2 == 0)
		throw std::invalid_argument("Grid size must be a positive odd integer.");

	int result = 0;
	for (int i = 1; i < n; i += 2)
	{
		result += i;
	}
	result = n + (2 * result);
	return result;
}

int MessageHandler::minDiamondGridSize(int messageLength) {
	if (messageLength < 0)
		throw std::invalid_argument("Message length must be > 0.");
	int n = 1;
	int diamondCount = diamondCellCount(n);
	while (diamondCount < messageLength) 
	{
		n += 2; // Only odd sizes
		diamondCount = diamondCellCount(n);
	}
	return n;
}

std::string MessageHandler::removeWhitespace(std::string str)
{
	str.erase(
		std::remove_if(str.begin(), str.end(),
			[](unsigned char c) { return std::isspace(c); }),
		str.end());
	return str;
}
