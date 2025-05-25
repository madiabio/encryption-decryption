#include "pch.h"
#include <sstream>
#include <iostream>

TEST(MessageHandlerTest, DefaultConstructorInitializesMembers) 
{
	MessageHandler h;
	EXPECT_EQ(h.getMsg(), "");
	EXPECT_EQ(h.getEncryptedMsg(), "");
	EXPECT_EQ(h.getTotalRounds(), 0);
	EXPECT_EQ(h.getGridSize(), 1);
    EXPECT_EQ(h.getCompletedRounds(), 0);
}

TEST(MessageHandlerTest, AutoGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "TRAGTARHEEEELAENDEKNNESNWOCOSRCNISDENAHTLOATCLUYM";
    MessageHandler h(message, encryptedMessage, 1);
    EXPECT_EQ(h.getMsg(), "GENERALTSONEEDSCHICKENNOW");
    EXPECT_EQ(h.getTotalRounds(), 1);
    EXPECT_EQ(h.getGridSize(), 7);
    EXPECT_EQ(h.getCompletedRounds(), 0);
}

TEST(MessageHandlerTest, ManualGridSizeConstructorInitializesMembers)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    std::string encryptedMessage = "TRAGTARHEEEELAENDEKNNESNWOCOSRCNISDENAHTLOATCLUYM";
    MessageHandler h(message, encryptedMessage, 1, 7);
    EXPECT_EQ(h.getMsg(), "GENERALTSONEEDSCHICKENNOW");
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
