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
