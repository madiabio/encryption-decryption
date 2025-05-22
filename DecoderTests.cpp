#include "gtest/gtest.h"
#include "Decoder.h"
#include "pch.h"

TEST(DecoderTest, EncryptedMessageNotOddPerfectSquare) 
{
	EXPECT_THROW(Decoder decoder("xxx", 1), std::invalid_argument);
}

TEST(DecoderTest, SingleRoundDecryptionGenTso)
{
    std::string message = "GENERAL TSO NEEDS CHICKEN NOW";
    int totalRounds = 1;

    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();

    Decoder d(encryptedMsg, totalRounds);

    EXPECT_EQ(d.getMsg(), "GENERALTSONEEDSCHICKENNOW");
}

TEST(DecoderTest, SingleRoundManualGridsizeMyFullNameSmallGrid)
{
    std::string message = "MADELINE ABIO";

    int gridSize = 5;
    int totalRounds = 1;

    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();

    Decoder d(encryptedMsg, totalRounds);

    EXPECT_EQ(d.getMsg(), "MADELINEABIO");
}

TEST(DecoderTest, SingleRoundManualGridsizeMyFullNameBigGrids)
{
    std::string message = "MADELINE ABIO";

    int totalRounds = 1;
    for (int gridSize = 6; gridSize < 100; ++gridSize) 
    {
        Encoder e(message, totalRounds);
        auto encryptedMsg = e.getEncryptedMsg();

        Decoder d(encryptedMsg, totalRounds);
        EXPECT_EQ(d.getMsg(), "MADELINEABIO");
    }
}

TEST(DecoderTest, TwoRoundEncryptionAutoGridSize)
{
    std::string message = "I ENJOY THIS COURSE";
    int totalRounds = 2;
    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();

    Decoder d(encryptedMsg, totalRounds);
    EXPECT_EQ(d.getMsg(), "IENJOYTHISCOURSE");
}

TEST(DecoderTest, ThreeRoundEncryptionAutoGridSize)
{
    std::string message = "I ENJOY THIS COURSE";
    int totalRounds = 3;
    Encoder e(message, totalRounds);
    auto encryptedMsg = e.getEncryptedMsg();

    Decoder d(encryptedMsg, totalRounds);
    EXPECT_EQ(d.getMsg(), "IENJOYTHISCOURSE");
}


