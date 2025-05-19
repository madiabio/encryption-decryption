#include "pch.h"
#include <sstream>
#include <iostream>

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
    EXPECT_EQ(h.getCompletedRounds(), 0);
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
    EXPECT_EQ(h.getCompletedRounds(), 0);
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
    EXPECT_EQ(h.getCompletedRounds(), 0);
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

TEST(MessageHandlerTest, SetNewMessageWorks)
{
    MessageHandler h;
    std::string newMsg = "new message";
    h.setMsg(newMsg);
    EXPECT_EQ(h.getMsg(), newMsg);
  
}

TEST(MessageHandlerTest, SetNewEncryptedMessageWorks)
{
    MessageHandler h;
    std::string newEncryptedMsg = "new encrypted message";
    h.setEncryptedMsg(newEncryptedMsg);
    EXPECT_EQ(h.getEncryptedMsg(), newEncryptedMsg);
}

TEST(MessageHandlerTest, SetNewGridSizeWorks)
{
    MessageHandler h;
    int newGridSize = 10;
    h.setGridSize(newGridSize);
    EXPECT_EQ(h.getGridSize(), newGridSize);

    newGridSize = -1;
    EXPECT_THROW(h.setGridSize(newGridSize), std::invalid_argument);
    
}
TEST(MessageHandlerTest, SetNewTotalRoundsWorks)
{
    MessageHandler h;
    int newTotalRounds = 2;
    h.setTotalRounds(newTotalRounds);
    EXPECT_EQ(h.getTotalRounds(), newTotalRounds);

    newTotalRounds = -1;
    EXPECT_THROW(h.setTotalRounds(newTotalRounds), std::invalid_argument);
}

TEST(MessageHandlerTest, SetNewCompletedRoundsWorks)
{
    MessageHandler h;
    int newCompletedRounds = 2;
    h.setCompletedRounds(newCompletedRounds);
    EXPECT_EQ(h.getCompletedRounds(), newCompletedRounds);

    newCompletedRounds = -1;
    EXPECT_THROW(h.setCompletedRounds(newCompletedRounds), std::invalid_argument);
}

TEST(MessageHandlerTest, PrintGridOutputsCorrectly) {
    // Arrange: create a MessageHandler with a known grid
    MessageHandler handler("", "ABCD", 1, 2); // 2x2 grid, encryptedMsg = "ABCD"

    // Redirect std::cout to a stringstream
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    // Act: print the grid
    handler.printGrid();

    // Restore std::cout
    std::cout.rdbuf(oldCout);

    // Output the captured string for visual inspection
    std::string output = buffer.str();
    std::cout << "Captured output:\n" << output << std::endl;

    // Optionally, assert on the output
    std::string expected =
        "A C\n"
        "B D\n";
    EXPECT_EQ(output, expected);
}