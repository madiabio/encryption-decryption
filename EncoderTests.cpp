#include "pch.h""
class TestEncoder : public Encoder {
public:
    using Encoder::Encoder; // Inherit constructors

    char getRandomLetter() override {
        return '*'; // Always return '*' for deterministic tests
    }
    using Encoder::makeGrid; // make makeGrid accessible
};

TEST(EncoderTest, DefaultConstructorInitializesMembers)
{
    TestEncoder encoder;
    EXPECT_EQ(encoder.getMsg(), "");
    EXPECT_EQ(encoder.getEncryptedMsg(), "");
    EXPECT_EQ(encoder.getTotalRounds(), 0);
    EXPECT_EQ(encoder.getGridSize(), 0);
}

TEST(EncoderTest, AutoGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "";
    TestEncoder encoder(message, 1);
    EXPECT_EQ(encoder.getMsg(), message);
    EXPECT_EQ(encoder.getEncryptedMsg(), encryptedMessage);
    EXPECT_EQ(encoder.getTotalRounds(), 1);
    EXPECT_EQ(encoder.getGridSize(), 7);

}
TEST(EncoderTest, ManualGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "";
    TestEncoder encoder(message, 1, 7);
    EXPECT_EQ(encoder.getMsg(), message);
    EXPECT_EQ(encoder.getEncryptedMsg(), encryptedMessage);
    EXPECT_EQ(encoder.getTotalRounds(), 1);
    EXPECT_EQ(encoder.getGridSize(), 7);
}

TEST(EncoderTest, AutoGridSizeConstructorThrowsForInvalidNumRounds)
{
    // number of rounds must be >=0
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    EXPECT_THROW(TestEncoder encoder(message, -1), std::invalid_argument);
}

TEST(EncoderTest, ManualGridSizeConstructorThrowsForInvalidNumRounds)
{
    // number of rounds must be >=0
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    EXPECT_THROW(TestEncoder encoder(message, -1, 7), std::invalid_argument);
}

TEST(EncoderTest, ManualGridSizeConstructorThrowsForInvalidGridSize)
{
    // Grid size must be <= 0.
    int g = -1;
    EXPECT_THROW(TestEncoder encoder("", 1, g), std::invalid_argument);
}


TEST(EncoderTest, ManualGridSizeConstructorThrowsForTooSmallGridSize)
{
    // Grid size must be <=7 for this to be valid.
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    int g = 6;
    EXPECT_THROW(TestEncoder encoder(message, 1, g), std::invalid_argument);
}

TEST(EncoderTest, ManualGridSizeConstructorThrowsForEvenGridSize)
{
    // Grid size must be an odd number.
    int g = 12;
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    EXPECT_THROW(TestEncoder encoder(message, 1, g), std::invalid_argument);
}

TEST(EncoderTest, MakeGridDiamondPattern) {
    std::string message = "ABCDE";
    int gridSize = 3; // Smallest odd grid for easy checking
    TestEncoder encoder(message, 1, gridSize);

    encoder.makeGrid();
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

    // Check diamond cells (adjust indices if your pattern is different)
    EXPECT_EQ(grid[1][0], 'A');
    EXPECT_EQ(grid[0][1], 'B');
    EXPECT_EQ(grid[1][2], 'C');
    EXPECT_EQ(grid[2][1], 'D');
    EXPECT_EQ(grid[1][1], 'E');

    // Check non-diamond cells are '*'
    EXPECT_EQ(grid[0][0], '*');
    EXPECT_EQ(grid[2][0], '*');
    EXPECT_EQ(grid[0][2], '*');
    EXPECT_EQ(grid[2][2], '*');
}