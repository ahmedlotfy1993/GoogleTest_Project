#include "LibraryCode.hpp"
#include <algorithm>
#include <stdexcept>
int sum(int a, int b){
	return a+b;
}
bool isPositive(int num){
	return num >= 0;
}
int CountPositives(const std::vector<int>& vec){
	return std::count_if(vec.begin(), vec.end(), isPositive);
}
Account::Account(): mBalance(0){}
void Account::deposit(double sum){
	mBalance += sum;
}
void Account::withdraw(double sum){
	if(mBalance < sum){
		throw std::runtime_error("Insufficient error");
	}
	mBalance -= sum;
}
double Account::getBalance()const{
	return mBalance;
}
void Account::transfer(Account& to, double sum){
	this->withdraw(sum);
	to.deposit(sum);
}
Validator::Validator(int low, int high):mLow(low), mHigh(high){
}
bool Validator::InRange(int val){
	return val >= mLow && val <= mHigh;
}
