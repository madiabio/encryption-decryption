#include "pch.h"
#include "Encoder.h"
#include <random>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>

Encoder::Encoder(const std::string& m, int r) : MessageHandler(m, "", r) 
{ 

    encrypt(); 
}

Encoder::Encoder(const std::string& m, int r, int g) : MessageHandler(m, "", r, g) 
{ 
    setGridSize(g); // update the grid size for the new string length
    encrypt(); 
}

char Encoder::getRandomLetter()
{
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    static std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(rng));
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
                if (msg[i] == '.') fullstop_placed = true;
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
                if (msg[i] == '.') fullstop_placed = true;
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
                if (msg[i] == '.') fullstop_placed = true;
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
                if (msg[i] == '.') fullstop_placed = true;
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
                if (msg[i] == '.') fullstop_placed = true;
                grid[gridSize / 2][gridSize / 2] = msg[i++];
            }
            else if (!fullstop_placed) {
                grid[gridSize / 2][gridSize / 2] = '.';
                fullstop_placed = true;
            }
        }
    }
}


void Encoder::encode()
{
    // Flatten grid.
    std::string newEncryptedMsg = "";
    for (size_t col = 0; col < grid.size(); ++col) {
        for (size_t row = 0; row < grid.size(); ++row) {
            newEncryptedMsg += grid[row][col];
        }
    }

    // Update encrypted msg
    setEncryptedMsg(newEncryptedMsg);
}

void Encoder::encrypt()
{

    // Make grid & encode based off of current params
    setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize))); // set the grid
    makeGrid();
    encode();
    setCompletedRounds(1);

    // If there's more rounds to do, handle it here.
    for (int round = 2; round <= totalRounds; ++round)
    {
        msg = encryptedMsg;
        setGridSize(pow(gridSize,2)); // update the grid size to be the next square number of the string length. This will make it be so that the decryptoin algrotihm can get gridsize as sqrt(len)
        setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize))); // set the grid
        makeGrid(); // make the grid again
        encode(); // update the encrypted msg with the new encrypted msg.
        setCompletedRounds(round); // finish the round
    }
}

