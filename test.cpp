#include <gtest/gtest.h>
#include "LibraryCode.hpp"

TEST(TestSuite, TestName){
	int summation = sum(2,4);
	ASSERT_EQ(6, summation);
}
int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
