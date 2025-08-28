#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <vector>
#include <utility>
#include "LibraryCode.hpp"

TEST(TestSuite, TestName){
	int summation = sum(2,4);
	ASSERT_EQ(6, summation);
}
TEST(TestCountPositiveSuite, TestBasic){
	std::vector<int> in {1,-2,3,-4,5,-6,7, -8};
	int num = CountPositives(in);
	ASSERT_EQ(4,num);
}
TEST(TestCountPositiveSuite, TestEmptyVec){
	std::vector<int> in {};
	int num = CountPositives(in);
	ASSERT_EQ(0, num);
}
class AccountTestFixture: public testing::Test{
	public:
		void SetUp() override;
		void TearDown() override;
		static void SetUpTestCase() ;
		static void TearDownTestCase() ;
	protected:
		Account account;

};
void AccountTestFixture::SetUp(){
	std::cout << "SetUp called" << std::endl;
	account.deposit(10.5);
}
void AccountTestFixture::TearDown(){
	std::cout << "TearDown called" << std::endl;
}
void AccountTestFixture::SetUpTestCase(){
	std::cout << "SetUpTestCase called" << std::endl;
}
void AccountTestFixture::TearDownTestCase(){
	std::cout << "TearDownTestCase called" << std::endl;
}
TEST_F(AccountTestFixture, TestDeposit){
	ASSERT_EQ(10.5, account.getBalance());
}
TEST_F(AccountTestFixture, TestUnsuffecientdeposit){
	ASSERT_THROW(account.withdraw(200), std::runtime_error);
}
class ValidatorFixture: public testing::TestWithParam<std::pair<int, bool>>{
	protected:
		Validator validator{5,10};
};
TEST_P(ValidatorFixture,TestValuesInRangeAndOutRange){
	auto parameter = GetParam();
	int value = parameter.first;
	int ex_res = parameter.second;
	std::cout << "Test value = " << value << " and expected result = " << ex_res << std::endl;
        ASSERT_EQ(ex_res, validator.InRange(value));	
}
std::vector<std::pair<int, bool>> my_vec{{-50, false}, {4, false}, {5, true}, {7, true}, {9,true}, {10, true}, {11, false}, {100, false}};
INSTANTIATE_TEST_SUITE_P(ANY_NAME, ValidatorFixture, testing::ValuesIn(my_vec));

class SomeClass{
	public:
		SomeClass()=default;
		virtual void some_method(){
			std::cout << "Say Something" << std::endl;
		}
};
class MockedClass: public SomeClass{
	public:
		MockedClass()=default;
		MOCK_METHOD(void, some_method, ());
};
TEST(Test_Gmock, Simple_Gmock){
	MockedClass mc;
	EXPECT_CALL(mc,some_method()).Times(1);
	mc.some_method();
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
