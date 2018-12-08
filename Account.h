#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <iostream>

using namespace std;

class Account{
	public:
		Account(string accountNumber);
		string getAccountNum() const;
		double getMoney() const;
		void bet(double moneyBet);
		void win(double moneyWon);
	private:
		string accountNumber;
		double money;
};
#endif
