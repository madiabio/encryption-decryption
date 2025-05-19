#include "pch.h"
#include "Encoder.h"
#include <random>
#include <ctime>
#include <string>
#include <vector>


Encoder::Encoder(const std::string& m, int r, int g) : MessageHandler(m, "", r, g)
{
    if (g % 2 == 0) throw std::invalid_argument("Grid size must be an odd number.");
    if (g < minDiamondGridSize(m.size())) throw std::invalid_argument("Grid size too small.");
    else gridSize = g;
}

char Encoder::getRandomLetter()
{
	// Seed the random number generator with the current time
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// Generate a random number between 0 and 25
	int randomNumber = std::rand() % 26;

	// Convert the random number to a capital letter (A=65, B=66, etc.)
	char randomLetter = static_cast<char>('A' + randomNumber);

	return randomLetter;
}

int Encoder::diamondCellCount(int n) {
    if (n <= 0 || n % 2 == 0)
        throw std::invalid_argument("Grid size must be a positive odd integer.");
    return n * n - ((n - 1) * (n - 1)) / 2;
}

int Encoder::minDiamondGridSize(int messageLength) {
    if (messageLength <= 0)
        throw std::invalid_argument("Message length must be positive.");
    int n = 1;
    while (diamondCellCount(n) < messageLength) {
        n += 2; // Only odd sizes
    }
    return n;
}

void Encoder::makeGrid()
{

    // Fill the grid with random uppercase letters
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            grid[row][col] = getRandomLetter(); // TODO: change to be a random letter after function is written.
        }
    }

    int i = 0;
    int starting_col = 0;
    while (i < msg.length() && starting_col < gridSize / 2) // once starting frm=om middle col, can't keep going anymore
    {
        int top_row_of_layer = starting_col;
        int bottom_row_of_layer = gridSize - top_row_of_layer;
        int current_col = starting_col; // col that's being interated on

        // up & right diagonal
        for (int row = gridSize / 2; row > top_row_of_layer; -row)
        {
            if (i == msg.length()) break;
            grid[row][current_col] = msg[i];
            i += 1;
            current_col += 1;
        }

        // down & right diagonal
        for (int row = top_row_of_layer; row < gridSize/2; ++row)
        {
            if (i == msg.length()) break;
            grid[row][current_col] = msg[i];
            i += 1;
            current_col += 1;
        }


        // down & left diagonal
        for (int row = gridSize/2; row < bottom_row_of_layer-1; ++row)
        {
            if (i == msg.length()) break;
            grid[row][current_col] = msg[i];
            i += 1;
            current_col -= 1;
        }


        // up & left diagonal
        for (int row = bottom_row_of_layer - 1; row < gridSize / 2; --row)
        {
            if (i == msg.length()) break;
            grid[row][current_col] = msg[i];
            i += 1;
            current_col -= 1;
        }

        starting_col += 1;
        if (starting_col == gridSize / 2) grid[gridSize / 2][gridSize / 2] = msg[i];
    }
}