#include "pch.h"

TEST(EncoderTest, DefaultConstructorInitializesMembers)
{
    Encoder encoder;
    EXPECT_EQ(encoder.getMsg(), "");
    EXPECT_EQ(encoder.getEncryptedMsg(), "");
    EXPECT_EQ(encoder.getTotalRounds(), 0);
    EXPECT_EQ(encoder.getGridSize(), 1);
}

TEST(EncoderTest, AutoGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERALTSONEEDSCHICKENNOW";
    std::string encryptedMessage = "";
    Encoder encoder(message, 1);
    EXPECT_EQ(encoder.getMsg(), message);
    EXPECT_EQ(encoder.getEncryptedMsg(), encryptedMessage);
    EXPECT_EQ(encoder.getTotalRounds(), 1);
    EXPECT_EQ(encoder.getGridSize(), 7);

}

TEST(EncoderTest, AutoGridSizeWorks)
{
    std::string message = "ABCDE";
    std::string encryptedMessage = "";
    Encoder encoder(message, 1);
    EXPECT_EQ(encoder.getMsg(), message);
    EXPECT_EQ(encoder.getEncryptedMsg(), encryptedMessage);
    EXPECT_EQ(encoder.getTotalRounds(), 1);
    EXPECT_EQ(encoder.getGridSize(),  3);
}

TEST(EncoderTest, ManualGridSizeConstructorFormatsMsgWithWhitespace)
{
    std::string message = "ABC DE";
    int gridSize = 5;
    Encoder encoder(message, 1, gridSize);
    EXPECT_EQ(encoder.getMsg(), "ABCDE");
}
TEST(EncoderTest, ManualGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "";
    Encoder encoder(message, 1, 7);
    EXPECT_EQ(encoder.getMsg(), "GENERALTSONEEDSCHICKENNOW");
    EXPECT_EQ(encoder.getEncryptedMsg(), encryptedMessage);
    EXPECT_EQ(encoder.getTotalRounds(), 1);
    EXPECT_EQ(encoder.getGridSize(), 7);
}

TEST(EncoderTest, AutoGridSizeConstructorThrowsForInvalidNumRounds)
{
    // number of rounds must be >= 0
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    EXPECT_THROW(Encoder encoder(message, -1), std::invalid_argument);
}

TEST(EncoderTest, ManualGridSizeConstructorThrowsForInvalidNumRounds)
{
    // number of rounds must be > 0
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    EXPECT_THROW(Encoder encoder(message, -1, 7), std::invalid_argument);
}

TEST(EncoderTest, ManualGridSizeConstructorThrowsForInvalidGridSize)
{
    // Grid size must be > 0.
    int g = -1;
    EXPECT_THROW(Encoder encoder("", 1, g), std::invalid_argument);
}


TEST(EncoderTest, ManualGridSizeConstructorThrowsForTooSmallGridSize)
{
    // Grid size must be <=7 for this to be valid.
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    int g = 6;
    EXPECT_THROW(Encoder encoder(message, 1, g), std::invalid_argument);
}

TEST(EncoderTest, ManualGridSizeConstructorThrowsForEvenGridSize)
{
    // Grid size must be an odd number.
    int g = 12;
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    EXPECT_THROW(Encoder encoder(message, 1, g), std::invalid_argument);
}

TEST(EncoderTest, MakeGridSimpleDiamondPattern) 
{
    std::string message = "ABCDE";
    int gridSize = 3; // Smallest odd grid for easy checking
    Encoder encoder(message, 1, gridSize);
    auto grid = encoder.getGrid();

    // The expected diamond pattern for 3x3:
    //   [ ][B][ ]
    //   [A][E][C]
    //   [ ][D][ ]

    // Check that the grid is the correct size
    ASSERT_EQ(grid.size(), gridSize);
    for (const auto& row : grid) {
        ASSERT_EQ(row.size(), gridSize);
    }

    // Optionally, print the grid for visual inspection
    std::cout << "Grid after makeGrid:\n";
    for (const auto& row : grid) {
        for (char c : row) std::cout << c << ' ';
        std::cout << '\n';
    }

    // Check diamond cells 
    EXPECT_EQ(grid[1][0], 'A');
    EXPECT_EQ(grid[0][1], 'B');
    EXPECT_EQ(grid[1][2], 'C');
    EXPECT_EQ(grid[2][1], 'D');
    EXPECT_EQ(grid[1][1], 'E');
}

TEST(EncoderTest, MakeGridAddsFullstopSimple)
{
    std::string message = "A";
    int gridSize = 3;
    Encoder encoder(message, 1, gridSize);

    auto grid = encoder.getGrid();

    EXPECT_EQ(grid[1][0], 'A');
    EXPECT_EQ(grid[0][1], '.');
}

TEST(EncoderTest, MakeGridAddsFullstopWhitespace)
{
    std::string message = "A B";
    int gridSize = 3;
    Encoder encoder(message, 1, gridSize);

    auto grid = encoder.getGrid();

    EXPECT_EQ(grid[1][0], 'A');
    EXPECT_EQ(grid[0][1], 'B');
    EXPECT_EQ(grid[1][2], '.');
}

TEST(EncoderTest, MakeGridDoesntDuplicateFullstop)
{
    std::string message = "A.";
    int gridSize = 3;
    Encoder encoder(message, 1, gridSize);

    auto grid = encoder.getGrid();

    EXPECT_EQ(grid[1][0], 'A');
    EXPECT_EQ(grid[0][1], '.');
    EXPECT_NE(grid[1][2], '.');
}


TEST(EncoderTest, OneRoundEncodingSimple)
{
    std::string message = "A.";
    int gridSize = 3;
    Encoder encoder(message, 1, gridSize);

    encoder.encode();
    auto encryptedMsg = encoder.getEncryptedMsg();

    EXPECT_EQ(encryptedMsg[1], 'A');
    EXPECT_EQ(encryptedMsg[3], '.');
}