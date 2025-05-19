#include "gtest/gtest.h"
#include "Decoder.h"
#include "pch.h"

TEST(DecoderTest, EncryptedMessageNotOddPerfectSquare) 
{
	EXPECT_THROW(Decoder decoder("xxx", 1), std::invalid_argument);
}

TEST(DecoderTest, FillsGridCorrectly) {
    // for a 3x3 grid, use "ABCDEFGHI"
    std::string encrypted = "ABCDEFGHI";
    Decoder decoder(encrypted, 1); // 1 round, gridSize will be 3

    auto grid = decoder.getGrid();

    // Expected grid after diagonal fill:
    // A D G
    // B E H
    // C F I
    EXPECT_EQ(grid[0][0], 'A');
    EXPECT_EQ(grid[0][1], 'D');
    EXPECT_EQ(grid[0][2], 'G');
    EXPECT_EQ(grid[1][0], 'B');
    EXPECT_EQ(grid[1][1], 'E');
    EXPECT_EQ(grid[1][2], 'H');
    EXPECT_EQ(grid[2][0], 'C');
    EXPECT_EQ(grid[2][1], 'F');
    EXPECT_EQ(grid[2][2], 'I');
}