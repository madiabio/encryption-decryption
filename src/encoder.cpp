#include "pch.h"
#include "../include/Encoder.h"
#include <random>
#include <ctime>
#include <string>
#include <vector>
#include <cmath>

Encoder::Encoder(const std::string& m, int r) : Encoder(m, r, minDiamondGridSize(removeWhitespace(m).size())) {}

Encoder::Encoder(const std::string& m, int r, int g)
{
    setMsg(m);
    setTotalRounds(r);
    setGridSize(g);
}
void Encoder::setGridSize(int g)
{
    if (g < 3) throw std::invalid_argument("Grid size must be greater than or equal to 3.");
    if (g % 2 == 0) throw std::invalid_argument("Grid size must be an odd number.");
    int minSize = minDiamondGridSize(getMsg().size());
    if (g < minSize) throw std::invalid_argument("Grid size too small for message length.");
    gridSize = g;
}

void Encoder::setGridSize()
{
    setGridSize(minDiamondGridSize(getMsg().size()));
}

void Encoder::setMsg(const std::string& m)
{
    auto newMsg = m;
    newMsg = removeWhitespace(m);
    // Check for more than one fullstop
    if (std::count(m.begin(), m.end(), '.') > 1)
        throw std::invalid_argument("Only one fullstop can be in the message.");

    // Check that all characters are A-Z, a-z, or '.'
    for (char c : newMsg) {
        if (c != '.' && !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            throw std::invalid_argument("Message can only contain letters A-Z, a-z, and at most one fullstop.");
        }
    }

    // Convert all letters to uppercase
    std::transform(newMsg.begin(), newMsg.end(), newMsg.begin(),
        [](unsigned char c) { return (c >= 'a' && c <= 'z') ? std::toupper(c) : c; });

    msg = newMsg;
}

void Encoder::makeGrid()
{
    // Fill the grid with random uppercase letters
    for (auto& row : grid) {
        std::generate(row.begin(), row.end(), [this]() { return getRandomLetter(); });
    }

    int i = 0;
    int starting_col = 0;
    bool fullstop_placed = false;

    while ((i < getMsg().length() || !fullstop_placed) && starting_col < (getGridSize() / 2)) {
        int top_row_of_layer = starting_col;
        int current_col = starting_col;

        // up & right diagonal
        for (int row = getGridSize() / 2; row > top_row_of_layer; --row) {
            if (getCompletedRounds() == 0) // if its the first round, handle the fullstop logic.
            {
                if (i < getMsg().length()) {
                    if (getMsg()[i] == '.') fullstop_placed = true;
                    grid[row][current_col] = getMsg()[i++];
                }
                else if (!fullstop_placed) {
                    grid[row][current_col] = '.';
                    fullstop_placed = true;
                }
            }
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < getMsg().length()) grid[row][current_col] = getMsg()[i++];
                else return;
            }
                    
            current_col++;
        }

        // down & right diagonal
        for (int row = top_row_of_layer; row < getGridSize() / 2; ++row) {
            if (getCompletedRounds() == 0) // if its the first round, handle fullstop logic.
            {
                if (i < getMsg().length()) {
                    if (getMsg()[i] == '.') fullstop_placed = true;
                    grid[row][current_col] = getMsg()[i++];
                }
                else if (!fullstop_placed) {
                    grid[row][current_col] = '.';
                    fullstop_placed = true;
                }
            }
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < getMsg().length()) grid[row][current_col] = getMsg()[i++];
                else return;
            }
            current_col++;
        }

        int bottom_row_of_layer = getGridSize() - top_row_of_layer;

        // down & left diagonal
        for (int row = getGridSize() / 2; row < bottom_row_of_layer - 1; ++row) {
            if (getCompletedRounds() == 0) // if its the first round, handle fullstop logic.
            {
                if (i < getMsg().length()) {
                    if (getMsg()[i] == '.') fullstop_placed = true;
                    grid[row][current_col] = getMsg()[i++];
                }
                else if (!fullstop_placed) {
                    grid[row][current_col] = '.';
                    fullstop_placed = true;
                }
            }
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < getMsg().length()) grid[row][current_col] = getMsg()[i++];
                else return;
            }
            current_col--;
        }

        // up & left diagonal
        for (int row = bottom_row_of_layer - 1; row > getGridSize() / 2; --row) {
            if (getCompletedRounds() == 0) // if its the first round, handle fullstop logic.
            {
                if (i < getMsg().length()) {
                    if (getMsg()[i] == '.') fullstop_placed = true;
                    grid[row][current_col] = getMsg()[i++];
                }
                else if (!fullstop_placed) {
                    grid[row][current_col] = '.';
                    fullstop_placed = true;
                }
            }
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < getMsg().length()) grid[row][current_col] = getMsg()[i++];
                else return;
            }
            current_col--;
        }

        starting_col++;
        if (starting_col == getGridSize() / 2) {
            if (getCompletedRounds() == 0) // if its the first round, handle fullstop logic.
            {
                // Center cell
                if (i < getMsg().length()) {
                    if (getMsg()[i] == '.') fullstop_placed = true;
                    grid[getGridSize() / 2][getGridSize() / 2] = getMsg()[i++];
                }
                else if (!fullstop_placed) {
                    grid[getGridSize() / 2][getGridSize() / 2] = '.';
                    fullstop_placed = true;
                }
            }
            else // if its not the first round, ignore fullstop logic.
            {
                if (i < getMsg().length()) grid[getGridSize() / 2][getGridSize() / 2] = getMsg()[i++];
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
    auto tempMsg = getMsg();
    auto tempGridSize = getGridSize();

    if (getMsg().empty()) throw std::invalid_argument("Encryption cannot be performed with empty msg.");
    if (getTotalRounds() < 1) throw std::invalid_argument("Encryption cannot be performed with total rounds set to less than 1.");

    while (getCompletedRounds() < getTotalRounds())
    {
        if (getCompletedRounds() == 0)
        {
            setMsg(getMsg());
            setGridSize(gridSize); // update the grid size to be what it was initially.
        }
        else
        {
            setMsg(getEncryptedMsg()); // update the msg to the current encrypted msg.
            setGridSize(minDiamondGridSize(getMsg().size())); // update the grid size to be the minimum grid size of the new msg.
        }

        setGrid(std::vector<std::vector<char>>(getGridSize(), std::vector<char>(getGridSize()))); // set the new grid
        makeGrid(); // make (fill) the new grid

        encode(); // update the encrypted msg with the new encrypted msg.
        setCompletedRounds(getCompletedRounds() + 1); // finish the round
        printRoundInfo("Encrypted", getEncryptedMsg());
    }

    setCompletedRounds(0); // reset completed rounds back to 0.
    setMsg(tempMsg); // reset msg back to what it was.
    setGridSize(tempGridSize); // reset grid size to minimum grid size.
}
