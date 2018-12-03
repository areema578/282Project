/* Name: Howard Chen And Scott Arima
 * ID: 005536087
 * Class: CECS 282
 * Instructor: Professor Minhthong Nguyen
 * Date: 30 November 2018
 * Purpose : This program is a video Black Jack Game
 * that has built in functions for account number login
 * betting money and Hit, Split, Stand.
 * 
 */
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
