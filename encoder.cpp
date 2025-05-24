#include "pch.h"
#include "Encoder.h"
#include <random>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>

Encoder::Encoder(const std::string& m, int r) : MessageHandler(m, "", r)
{ 
    setMsg(removeWhitespace(m));
    setGridSize(minDiamondGridSize(msg.size()));
}

Encoder::Encoder(const std::string& m, int r, int g) : MessageHandler(m, "", r)
{ 
    setMsg(removeWhitespace(m));
    setGridSize(g);
}

void Encoder::setGridSize(int g)
{
    if (g < 3) throw std::invalid_argument("Grid size must be greater than or equal to 3.");
    if (g % 2 == 0) throw std::invalid_argument("Grid size must be an odd number.");
    int minSize = minDiamondGridSize(msg.size());
    if (g < minSize) throw std::invalid_argument("Grid size too small for message length.");
    gridSize = g;

}

void Encoder::setMsg(const std::string& m)
{
    // Check for more than one fullstop
    if (std::count(m.begin(), m.end(), '.') > 1)
        throw std::invalid_argument("Only one fullstop can be in the message.");

    // Check that all characters are A-Z, a-z, or '.'
    for (char c : m) {
        if (c != '.' && !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            throw std::invalid_argument("Message can only contain letters A-Z, a-z, and at most one fullstop.");
        }
    }

    if (m.empty()) throw std::invalid_argument("Message cannot be empty.");

    // Convert all letters to uppercase
    std::string upperMsg = m;
    std::transform(upperMsg.begin(), upperMsg.end(), upperMsg.begin(),
        [](unsigned char c) { return (c >= 'a' && c <= 'z') ? std::toupper(c) : c; });

    msg = upperMsg;
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
            if (completedRounds == 0) // if its the first round, handle the fullstop logic.
            {
                if (i < msg.length()) {
                    if (msg[i] == '.') fullstop_placed = true;
                    grid[row][current_col] = msg[i++];
                }
                else if (!fullstop_placed) {
                    grid[row][current_col] = '.';
                    fullstop_placed = true;
                }
            }
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < msg.length()) grid[row][current_col] = msg[i++];
                else return;
            }
                    
            current_col++;
        }

        // down & right diagonal
        for (int row = top_row_of_layer; row < gridSize / 2; ++row) {
            if (completedRounds == 0) // if its the first round, handle fullstop logic.
            {
                if (i < msg.length()) {
                    if (msg[i] == '.') fullstop_placed = true;
                    grid[row][current_col] = msg[i++];
                }
                else if (!fullstop_placed) {
                    grid[row][current_col] = '.';
                    fullstop_placed = true;
                }
            }
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < msg.length()) grid[row][current_col] = msg[i++];
                else return;
            }
            current_col++;
        }

        int bottom_row_of_layer = gridSize - top_row_of_layer;

        // down & left diagonal
        for (int row = gridSize / 2; row < bottom_row_of_layer - 1; ++row) {
            if (completedRounds == 0) // if its the first round, handle fullstop logic.
            {
                if (i < msg.length()) {
                    if (msg[i] == '.') fullstop_placed = true;
                    grid[row][current_col] = msg[i++];
                }
                else if (!fullstop_placed) {
                    grid[row][current_col] = '.';
                    fullstop_placed = true;
                }
            }
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < msg.length()) grid[row][current_col] = msg[i++];
                else return;
            }
            current_col--;
        }

        // up & left diagonal
        for (int row = bottom_row_of_layer - 1; row > gridSize / 2; --row) {
            if (completedRounds == 0) // if its the first round, handle fullstop logic.
            {
                if (i < msg.length()) {
                    if (msg[i] == '.') fullstop_placed = true;
                    grid[row][current_col] = msg[i++];
                }
                else if (!fullstop_placed) {
                    grid[row][current_col] = '.';
                    fullstop_placed = true;
                }
            }
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < msg.length()) grid[row][current_col] = msg[i++];
                else return;
            }
            current_col--;
        }

        starting_col++;
        if (starting_col == gridSize / 2) {
            if (completedRounds == 0) // if its the first round, handle fullstop logic.
            {
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
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < msg.length()) grid[gridSize / 2][gridSize / 2] = msg[i++];
                else return;
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
    // for one round:

    // Make grid & encode based off of current params
    
    setMsg(msg); // check msg is ok.
    setGridSize(gridSize); // check grid size is ok.
    setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize))); // set the grid
    makeGrid();
    encode();
    setCompletedRounds(1);
    printRoundInfo("Encrypted", encryptedMsg);

    
    // If there's more rounds to do, handle it here.
    while (completedRounds < totalRounds)
    {
        setMsg(encryptedMsg); // update the msg to the current encrypted msg.
        setGridSize(minDiamondGridSize(msg.size())); // update the grid size to be the minimum grid size of the new msg.
        
        setGrid(std::vector<std::vector<char>>(gridSize, std::vector<char>(gridSize))); // set the new grid
        makeGrid(); // make (fill) the new grid

        encode(); // update the encrypted msg with the new encrypted msg.
        setCompletedRounds(completedRounds + 1); // finish the round
        printRoundInfo("Encrypted", encryptedMsg);
    }
}

