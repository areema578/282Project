#include "Card.h"
#include "Player.h"
#include "Account.h"
#include "Deck.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
	
	string menu = "Choose number option:\n1. Hit\n2. Stand\n3. Split";
	string one = "1";
	string two = "2";
	string three = "3";
	string hitOptions = "Choose number option:\n1. Hit first hand only\n2. Hit second hand only\n3. Hit both hands";
	string hitChoice; //different choices on what to hit
	
	//create the deck of cards
	Deck deckCreator;
	vector<Card> deck = deckCreator.getDeck();
	
	double pot;
	double totalBet = 0; //overall amount bet
	double amountWon = 0; //overall earnings
	string play = "Yes";
	string choice; //whether to play again
	string option; //chooses what the user wants to do (hit, stand, split)
	bool isSplit = false;
	cout<<fixed<<setprecision(2);
	
	cout<<"We are going to play Blackjack."<<endl;
	cout<<"Enter your account number: ";
	string accountNumber;
	cin>>accountNumber;
	Account account(accountNumber);
	
	do{
		cout<<"Your current balance is $"<<account.getMoney()<<endl;
		cout<<"Enter the amount of money you would like to bet: ";
		double money;
		cin>>money;
		account.bet(money);
		pot = money; //amount for the round
		totalBet += money;
		
		Player dealer;
		Player user;
		
		//initial dealing 
		user.hit(deck[0]); //example dealing, not final
		user.hit(deck[1]);
		user.seeHand();
		dealer.hit(deck[2]);
		dealer.hit(deck[3]);
		dealer.seeDealerHand();
		
		cout<<menu<<endl;
		cin>>option;
		while(option != two){
			if(option == one){
				if(isSplit == false){ //doesn't have a second hand
					if(user.isDone()){
						cout<<"You can't hit anymore; you have "<<user.getTotalValue()<<endl;
					}
					else{
						user.hit(deck[4]); //example dealing
						user.seeHand();	
					}
				}
				else{ //does have a second hand
					cout<<hitOptions<<endl;
					cin>>hitChoice;
					if(hitChoice == one){ //hit first hand
						if(user.isDone()){
							cout<<"You can't hit anymore; you have "<<user.getTotalValue()<<endl;
						}
						else{
							user.hit(deck[10]);
							user.seeHand();	
						}
					}
					else if(hitChoice == two){ //hit second hand
						if(user.isDoneSplit()){
							cout<<"You can't hit anymore; you have "<<user.getSplitTotalValue()<<endl;
						}
						else{
							user.hitSplit(deck[11]);
							user.seeSplitHand();
						}
					}
					else if(hitChoice == three){ //hit both hands
						if(user.isDone()){
							cout<<"You can't hit anymore in your first hand; you have "<<user.getTotalValue()<<endl;
						}
						else{
							user.hit(deck[12]);
							user.seeHand();	
						}
						if(user.isDoneSplit()){
							cout<<"You can't hit anymore in your second hand; you have "<<user.getSplitTotalValue()<<endl;
						}
						else{
							user.hitSplit(deck[13]);
							user.seeSplitHand();
						}
					}
				}
			}
			else if(option == three){ //you want to split when you have duplicate cards
				isSplit = true;
				account.bet(pot);
				totalBet += pot;
				pot *= 2;
				cout<<"The pot is now at $"<<pot<<endl;
				user.hitSplit(deck[5]); //example dealing
				user.hitSplit(deck[6]); //according to the instructions, when you split you get two cards to that hand
				user.seeSplitHand();
			}
			cout<<menu<<endl;
			cin>>option;
			//if option is stand then the user is done getting cards
		}
		
		//end of the round, displaying the total values of the hands, determing the winner
		if(isSplit){
			cout<<"Total value for your first hand: "<<user.getTotalValue()<<endl;
			cout<<"Total value for your second hand: "<<user.getSplitTotalValue()<<endl;
			if(user.getTotalValue() > 21 && user.getSplitTotalValue() > 21){
				cout<<"Both your hands have exceeded 21; you lost this round"<<endl;
				pot = 0;
			}
			else{
				cout<<"Total value for the dealer's hand: "<<dealer.getTotalValue()<<endl;
				while(dealer.getTotalValue() < 17){
					dealer.hit(deck[7]); //continues to draw until his hand is 17 or above
					cout<<"Dealer hits: "<<deck[7].getName()<<endl;
				}
				if(dealer.getTotalValue() > 21){
					cout<<"Dealer has exceeded 21; you won this round"<<endl;
					pot *= 2;
					account.win(pot);
					amountWon += pot;
					pot = 0;
				}
				else if((dealer.getTotalValue() <= user.getTotalValue() && user.getTotalValue() < 22) || (dealer.getTotalValue() <= user.getSplitTotalValue() && user.getSplitTotalValue() < 22)){
					if(dealer.getTotalValue() == user.getTotalValue() || dealer.getTotalValue() == user.getSplitTotalValue()){
						cout<<"You tied; you split the pot"<<endl;
						pot /= 2;
						account.win(pot);
						amountWon += pot;
						pot = 0;
					}
					else{
						cout<<"You beat the dealer's hand; you won this round"<<endl;
						pot *= 2;
						account.win(pot);
						amountWon += pot;
						pot = 0;
					}
				}
				else{
					cout<<"The dealer's hand beat both your hands; you lost this round"<<endl;
					pot = 0;
				}
			}
		}
		else{
			cout<<"Total value for your hand: "<<user.getTotalValue()<<endl;
			if(user.getTotalValue() > 21){
				cout<<"You have exceeded 21; you lost this round"<<endl;
				pot = 0;
			}
			else{
				cout<<"Total value for the dealer's hand: "<<dealer.getTotalValue()<<endl;
				while(dealer.getTotalValue() < 17){
					dealer.hit(deck[7]); //continues to draw until his hand is 17 or above
					cout<<"Dealer hits: "<<deck[7].getName()<<endl;
				}
				if(dealer.getTotalValue() > 21){
					cout<<"Dealer has exceeded 21; you won this round"<<endl;
					pot *= 2;
					account.win(pot);
					amountWon += pot;
					pot = 0;
				}
				else if(dealer.getTotalValue() == user.getTotalValue()){
					cout<<"You tied; you split the pot"<<endl;
					pot /= 2;
					account.win(pot);
					amountWon += pot;
					pot = 0;
				}
				else if(dealer.getTotalValue() < user.getTotalValue()){
					cout<<"You beat the dealer's hand; you won this round"<<endl;
					pot *= 2;
					account.win(pot);
					amountWon += pot;
					pot = 0;
				}
				else{
					cout<<"The dealer had a "<<dealer.getTotalValue()<<"; you lost this round"<<endl;
					pot = 0;
				}
			}
		}
		cout<<"Would you like to play again? (Yes/No): ";
		cin>>choice;
	}while(choice == play);
	
	cout<<"Total amount of betting money: $"<<totalBet<<endl;
	cout<<"Total amount won: $"<<amountWon<<endl;
	
	return 0;
}
