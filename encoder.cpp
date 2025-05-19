#include "pch.h"
#include "Encoder.h"
#include <random>
#include <ctime>
#include <string>
#include <vector>



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

void Encoder::makeGrid()
{
    // Fill the grid with random uppercase letters
    for (int row = 0; row < gridSize; ++row) {
        for (int col = 0; col < gridSize; ++col) {
            grid[row][col] = getRandomLetter();
        }
    }

    int i = 0;
    int starting_col = 0;
    bool fullstop_placed = false;

    while ((i < msg.length() || !fullstop_placed) && starting_col < (gridSize / 2)) {
        int top_row_of_layer = starting_col;
        int current_col = starting_col;

        // up & right diagonal
        for (int row = gridSize / 2; row > top_row_of_layer; --row) {
            if (i < msg.length()) {
                grid[row][current_col] = msg[i++];
            }
            else if (!fullstop_placed) {
                grid[row][current_col] = '.';
                fullstop_placed = true;
            }
            current_col++;
        }

        // down & right diagonal
        for (int row = top_row_of_layer; row < gridSize / 2; ++row) {
            if (i < msg.length()) {
                grid[row][current_col] = msg[i++];
            }
            else if (!fullstop_placed) {
                grid[row][current_col] = '.';
                fullstop_placed = true;
            }
            current_col++;
        }

        int bottom_row_of_layer = gridSize - top_row_of_layer;

        // down & left diagonal
        for (int row = gridSize / 2; row < bottom_row_of_layer - 1; ++row) {
            if (i < msg.length()) {
                grid[row][current_col] = msg[i++];
            }
            else if (!fullstop_placed) {
                grid[row][current_col] = '.';
                fullstop_placed = true;
            }
            current_col--;
        }

        // up & left diagonal
        for (int row = bottom_row_of_layer - 1; row > gridSize / 2; --row) {
            if (i < msg.length()) {
                grid[row][current_col] = msg[i++];
            }
            else if (!fullstop_placed) {
                grid[row][current_col] = '.';
                fullstop_placed = true;
            }
            current_col--;
        }

        starting_col++;
        if (starting_col == gridSize / 2) {
            // Center cell
            if (i < msg.length()) {
                grid[gridSize / 2][gridSize / 2] = msg[i++];
            }
            else if (!fullstop_placed) {
                grid[gridSize / 2][gridSize / 2] = '.';
                fullstop_placed = true;
            }
        }
    }
}

std::string Encoder::removeWhitespace(std::string str)
{
    str.erase(
        std::remove_if(str.begin(), str.end(),
            [](unsigned char c) { return std::isspace(c); }),
        str.end());
    return str;
}