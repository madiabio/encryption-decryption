#include "pch.h""

TEST(EncoderTest, DefaultConstructorInitializesMembers)
{
    Encoder e;
    EXPECT_EQ(e.getMsg(), "");
    EXPECT_EQ(e.getEncryptedMsg(), "");
    EXPECT_EQ(e.getTotalRounds(), 0);
    EXPECT_EQ(e.getGridSize(), 0);
}

TEST(EncoderTest, AutoGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "";
    Encoder e(message, 1);
    EXPECT_EQ(e.getMsg(), message);
    EXPECT_EQ(e.getEncryptedMsg(), encryptedMessage);
    EXPECT_EQ(e.getTotalRounds(), 1);
    EXPECT_EQ(e.getGridSize(), 7);

}

TEST(EncoderTest, ManualGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "";
    Encoder e(message, 1, 7);
    EXPECT_EQ(e.getMsg(), message);
    EXPECT_EQ(e.getEncryptedMsg(), encryptedMessage);
    EXPECT_EQ(e.getTotalRounds(), 1);
    EXPECT_EQ(e.getGridSize(), 7);
}

TEST(EncoderTest, AutoGridSizeConstructorThrowsForInvalidNumRounds)
{
    // number of rounds must be >=0
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "";
    EXPECT_THROW(Encoder e(message, -1), std::invalid_argument);
}

TEST(EncoderTest, ManualGridSizeConstructorThrowsForInvalidNumRounds)
{
    // number of rounds must be >=0
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "";
    EXPECT_THROW(Encoder e(message, -1, 7), std::invalid_argument);
}

TEST(EncoderTest, ManualGridSizeConstructorThrowsForInvalidGridSize)
{
    // Grid size must be <=7 for this to be valid.
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "";
    EXPECT_THROW(Encoder e(message, -1, 6), std::invalid_argument);
}
