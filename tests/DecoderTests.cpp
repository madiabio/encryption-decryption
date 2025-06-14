#include "pch.h"
#include "gtest/gtest.h"
#include "Decoder.h"

TEST(DecoderTest, EncryptedMessageNotOddPerfectSquare) 
{
	EXPECT_THROW(Decoder decoder("xxx", 1), std::invalid_argument);
}

TEST(DecoderTest, FillsGridCorrectly) {
	// Tests the grid is filled correctly with the encrypted message.

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

TEST(DecoderTest, SingleRoundDecryptionGenTso)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    int totalRounds = 1;

    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();

    Decoder d(encryptedMsg, totalRounds);

    EXPECT_EQ(d.getMsg(), e.getMsg());
}

TEST(DecoderTest, SingleRoundManualGridsizeMyFullNameSmallGrid)
{
    std::string message = "MADELINEABIO";
    int gridSize = 5;
    int totalRounds = 1;

    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();

    Decoder d(encryptedMsg, totalRounds);

    EXPECT_EQ(d.getMsg(), e.getMsg());
}

TEST(DecoderTest, SingleRoundManualGridsizeMyFullNameBigGrids)
{
    std::string message = "MADELINEABIO";

    int totalRounds = 1;
    for (int gridSize = 6; gridSize < 100; ++gridSize) 
    {
        Encoder e(message, totalRounds);
        auto encryptedMsg = e.getEncryptedMsg();

        Decoder d(encryptedMsg, totalRounds);
        EXPECT_EQ(d.getMsg(), e.getMsg());
    }
}

TEST(DecoderTest, TwoRoundDecryptionWorksSimple)
{
    std::string message = "A.";
    int numRounds = 2;
    int gridSize = 3;
    Encoder e(message, numRounds, gridSize);

    auto encryptedMsg = e.getEncryptedMsg();

    Decoder d(encryptedMsg, numRounds);

    std::string decryptedMsg = d.getMsg();

    EXPECT_EQ("A", decryptedMsg);
}

TEST(DecoderTest, ThreeRoundDecryptionWorksSimple)
{
    std::string message = "A.";
    int numRounds = 3;
    int gridSize = 3;
    Encoder e(message, numRounds, gridSize);

    auto encryptedMsg = e.getEncryptedMsg();

    Decoder d(encryptedMsg, numRounds);

    std::string decryptedMsg = d.getMsg();

    EXPECT_EQ("A", decryptedMsg);
}

TEST(DecoderTest, Scenario1)
{
    std::string message = "MADELINEABIO";
    int totalRounds = 1;
    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();
    Decoder d(encryptedMsg, totalRounds);
	EXPECT_EQ(d.getMsg(), e.getMsg());
}

TEST(DecoderTest, Scenario2)
{
    std::string message = "MADELINEABIO";
    int totalRounds = 1;
    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();
    Decoder d(encryptedMsg, totalRounds);
	EXPECT_EQ(d.getMsg(), e.getMsg());
}

TEST(DecoderTest, TwoRoundScenario3)
{
    std::string message = "I ENJOY THIS COURSE";
    int totalRounds = 2;
    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();
    Decoder d(encryptedMsg, totalRounds);
    EXPECT_EQ(d.getMsg(), "IENJOYTHISCOURSE");

}
TEST(DecoderTest, Scenario3)
{
    std::string message = "I ENJOY THIS COURSE";
    int totalRounds = 3;
    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();
    Decoder d(encryptedMsg, totalRounds);
    EXPECT_EQ(d.getMsg(), "IENJOYTHISCOURSE");
}