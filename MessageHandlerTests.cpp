#include "pch.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(MessageHandlerTest, DefaultConstructorInitializesMembers) 
{
	MessageHandler h;
	EXPECT_EQ(h.getMsg(), "");
	EXPECT_EQ(h.getEncryptedMsg(), "");
	EXPECT_EQ(h.getTotalRounds(), 0);
	EXPECT_EQ(h.getGridSize(), 0);
    EXPECT_EQ(h.getRoundsCompleted(), 0);
}

TEST(MessageHandlerTest, AutoGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "TRAGTARHEEEELAENDEKNNESNWOCOSRCNISDENAHTLOATCLUYM";
    MessageHandler h(message, encryptedMessage, 1);
    EXPECT_EQ(h.getMsg(), message);
    EXPECT_EQ(h.getEncryptedMsg(), encryptedMessage);
    EXPECT_EQ(h.getTotalRounds(), 1);
    EXPECT_EQ(h.getGridSize(), 7);
    EXPECT_EQ(h.getRoundsCompleted(), 0);
}

TEST(MessageHandlerTest, ManualGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "TRAGTARHEEEELAENDEKNNESNWOCOSRCNISDENAHTLOATCLUYM";
    MessageHandler h(message, encryptedMessage, 1, 7);
    EXPECT_EQ(h.getMsg(), message);
    EXPECT_EQ(h.getEncryptedMsg(), encryptedMessage);
    EXPECT_EQ(h.getTotalRounds(), 1);
    EXPECT_EQ(h.getGridSize(), 7);
    EXPECT_EQ(h.getRoundsCompleted(), 0);
}

TEST(MessageHandlerTest, AutoGridSizeConstructorThrowsForInvalidNumRounds)
{
    // number of rounds must be >=0
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "TRAGTARHEEEELAENDEKNNESNWOCOSRCNISDENAHTLOATCLUYM";
    EXPECT_THROW(MessageHandler h(message, encryptedMessage, -1), std::invalid_argument);
}

TEST(MessageHandlerTest, ManualGridSizeConstructorThrowsForInvalidNumRounds)
{
    // number of rounds must be >=0
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "TRAGTARHEEEELAENDEKNNESNWOCOSRCNISDENAHTLOATCLUYM";
    EXPECT_THROW(MessageHandler h(message, encryptedMessage, -1, 7), std::invalid_argument);
}

TEST(MessageHandlerTest, ManualGridSizeConstructorThrowsForInvalidGridSize)
{
    // Grid size must be <=7 for this to be valid.
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "TRAGTARHEEEELAENDEKNNESNWOCOSRCNISDENAHTLOATCLUYM";
    EXPECT_THROW(MessageHandler h(message, encryptedMessage, -1, 6), std::invalid_argument);
}

TEST(MessageHandlerTest, PrintGridWorksForForSetGridSize)
{
	std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
	std::string encryptedMessage = "TRAGTARHEEEELAENDEKNNESNWOCOSRCNISDENAHTLOATCLUYM";
	MessageHandler h(message, encryptedMessage, 0, 7);

    // Redirect std::cout to a stringstream
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    h.printGrid();

    // Restore std::cout
    std::cout.rdbuf(oldCout);

    std::string output = buffer.str();

    // Split output into lines
    std::vector<std::string> lines;
    std::istringstream iss(output);
    std::string line;
    while (std::getline(iss, line)) {
        lines.push_back(line);
    }

    // Diamond positions for a 7x7 grid (0-based indexing)
    // Row:    Cols:
    // 0       3
    // 1     2 3 4
    // 2   1 2 3 4 5
    // 3 0 1 2 3 4 5 6
    // 4   1 2 3 4 5
    // 5     2 3 4
    // 6       3

    std::vector<std::vector<int>> diamondIndices = {
        {3},
        {2,3,4},
        {1,2,3,4,5},
        {0,1,2,3,4,5,6},
        {1,2,3,4,5},
        {2,3,4},
        {3}
    };

    std::string diamondChars;
    for (size_t row = 0; row < diamondIndices.size() && row < lines.size(); ++row) {
        for (int col : diamondIndices[row]) {
            if (col < lines[row].size() && std::isupper(lines[row][col])) {
                diamondChars += lines[row][col];
            }
        }
    }

    // Set your expected diamond string (left-to-right, top-to-bottom)
    std::string expected = "ENSREDNCAGEEWNHLEKOITNCSO"; // Replace with your actual expected diamond

    EXPECT_EQ(diamondChars, expected);
}

TEST(MessageHandlerTest, Set)
{

}