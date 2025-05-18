#include "pch.h"
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(MessageHandlerConstructorsTest, DefaultConstructorInitializesMembers) {
	MessageHandler h;
	EXPECT_EQ(h.getMsg(), "");
	EXPECT_EQ(h.getEncryptedMsg(), "");
	EXPECT_EQ(h.getRounds(), 0);
	EXPECT_EQ(h.getGridSize(), 0);
}
