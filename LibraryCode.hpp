#pragma once
#include <vector>
int sum(int a, int b);
bool isPositive(int num);
int CountPositives(const std::vector<int>& vec);
class Account{
	double mBalance;
	public:
		Account();
		void deposit(double sum);
		void withdraw(double sum);
		double getBalance()const;
		void transfer(Account& to, double sum);
};
class Validator{
	int mLow;
	int mHigh;
	public:
		Validator(int low, int high);
		bool InRange(int val);
};
