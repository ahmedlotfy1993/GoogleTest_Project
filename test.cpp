#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include "LibraryCode.hpp"
#include "IDatabaseConnection.hpp"
#include "EmployeeManager.hpp"

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
/******************************************************************************USING TEST FIXTURE****************************************************************************/
/*!
* Override the setup and teardown method to avoid rewrite the same initial steps for every test case
* The name of test suite should be with the name of the class which inherit from Test class
* For every individual test case the setup and tear down are called
* Virtual methods (incase your test fixture is being inherited ) call be called from SetUp and TearDown but can not called from the constructor and destructor
* function can throw exception should be called from the TearDown not from the destructor of test case
* static function set up test case and tear down test case are called once at the begin and at the end.
*/
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

/*****************************************************************USING PRAMETERIZED TESTS**************************************************************/
/*!
 * When tests bodies is the same but the input is different
 * Extend the template class Testing with param class and the template arguments are your input format
 * So we write it one time by calling instantiate test suite instead of write it over and over and give it the your input list and the class name for test suite
*/
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

/***************************************************USING GMOCK*************************************************************************/
/*!
 * This useful to isolate a class from it's dependancies, by  extending a class and mocking it's method(override) by MOCK_METHOD
*/
class SomeClass{
	public:
		SomeClass()=default;
		virtual void some_method(){
			std::cout << "Say Something" << std::endl;
		}
};
/*! 
* Use parantheis for complex types or when the input are more than 2
* It's optional to mention the specification for the mocked method at the end parameter(const, noexcept)
* To test the function is called you can use EXPECT_CALL with the child class and the overriden method and expect how times will be called.
*/
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

class MockDatabaseConnection : public IDatabaseConnection
{
public:
    MockDatabaseConnection(std::string serverAddress);

	MOCK_METHOD(void, connect, (), (override));
	MOCK_METHOD(void, disconnect, (), (override));
	MOCK_METHOD(float, getSalary, (int) , (const, override));
	MOCK_METHOD(void, updateSalary, (int, float), (override));
	MOCK_METHOD((std::vector<Employee>), getSalariesRange, (float), (const, override));
	MOCK_METHOD((std::vector<Employee>), getSalariesRange, (float, float), (const, override));
};

MockDatabaseConnection::MockDatabaseConnection(std::string serverAddress) : IDatabaseConnection(serverAddress)
{

}
/*!
 * List the expected calls inside the test case body before making the calls to the functions explicitly or implicitly
*/
TEST(TestEmployeeManager, TestConnection)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());

    EmployeeManager employeeManager(&dbConnection);
}
/*!
 *  The test case show when don't care about input parameters by using matchers testing::_
*/
TEST(TestEmployeeManager, TestUpdateSalary)
{
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, updateSalary(testing::_, testing::_)).Times(1);   

    EmployeeManager employeeManager(&dbConnection);

    employeeManager.setSalary(50, 6000);
}
/*!
 *  The test case show when don't care about input parameters by using matchers testing::_ .
 * Use WillOnce to expect the return value by testing::Return()
*/
TEST(TestEmployeeManager, TestGetSalary)
{
    const int employeeId = 50;
    const float salary = 6100.0;
    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, getSalary(testing::_)).Times(1).WillOnce(testing::Return(salary));

    EmployeeManager employeeManager(&dbConnection);

    float returnedSalary = employeeManager.getSalary(employeeId);

    ASSERT_EQ(salary, returnedSalary);
}
/*!
* Use WillOnce to force throwing an exception and use ASSERT_THROW to execute the function call and test the throw
*/
TEST(TestEmployeeManager, TestConnectionError){
	MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect()).WillOnce(testing::Throw(std::runtime_error("Dummy error")));
	ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}
/*!
* Use ACTION macro to specify action like a function consist of multiple lines.
*/
ACTION(myAction){
	std::cout << "Throwing an error\n";
	throw std::runtime_error("Dummy error"");
}
TEST(TestEmployeeManager, TestConnectionErrorAction){
	MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect()).WillOnce(myAction());
	ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}
/*!
* Use testing::Invoke() which forward the parameters from mocked function to the callable inside testing::Invoke
*/
void myAction(void){
	std::cout << "Throwing an error\n";
	throw std::runtime_error("Dummy error"");
}
TEST(TestEmployeeManager, TestConnectionErrorActionInvoke){
	MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect()).WillOnce(testing::Invoke(myAction));
	ASSERT_THROW(EmployeeManager employeeManager(&dbConnection), std::runtime_error);
}
TEST(TestEmployeeManager, TestGetSalaryInRange)
{
    const int low = 5000, high = 8000;
    std::vector<Employee> returnedVector{Employee{1, 5600, "John"},
                                    Employee{2, 7000, "Jane"},
                                    Employee{3, 6600, "Alex"}};

    MockDatabaseConnection dbConnection("dummyConnection");
    EXPECT_CALL(dbConnection, connect());
    EXPECT_CALL(dbConnection, disconnect());
    EXPECT_CALL(dbConnection, getSalariesRange(low, high)).WillOnce(testing::Return(returnedVector));

    EmployeeManager employeeManager(&dbConnection);

    std::map<std::string, float> returnedMap = employeeManager.getSalariesBetween(low, high);

    for(auto it=returnedMap.begin(); it!=returnedMap.end(); ++it)
    {
        std::cout << it->first << " " << it->second << '\n';
        ASSERT_THAT(it->second, testing::AnyOf(testing::Gt(low), testing::Lt(high-3000)));
    }
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
