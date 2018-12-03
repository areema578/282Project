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
#include "Account.h"

Account::Account(string accountNumber){
	this->accountNumber = accountNumber;
	money = 50.00;
}

string Account::getAccountNum() const {
	return accountNumber;
}

double Account::getMoney() const {
	return money;
}

void Account::bet(double moneyBet){
	if(moneyBet > money){
		cout<<"You dont have enough money to bet that amount"<<endl;
		cout<<"You bet your remaning balance of $"<<money<<endl;
		money = 0.00;
	}else{
		money -= moneyBet;
		cout<<"You bet $"<<moneyBet<<endl;
		cout<<"You have $"<<money<<" left"<<endl;
	}
}

void Account::win(double moneyWon){
	money += moneyWon;
	cout<<"You won $"<<moneyWon<<endl;
	cout<<"Your total balance is $"<<money<<endl;
}
