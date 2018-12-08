/* Name: Howard Chen, Scott Arima
 * ID: 005536087, 014073486
 * Class: CECS 282
 * Instructor: Professor Minhthong Nguyen
 * Date: 08 Decemeber 2018
 * Purpose : Program is a text based game of Black Jack.
 *
 */
#include "Card.h"
#include "Player.h"
#include "Account.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

// random int generator for shuffling deck
int randomFunc (int i) { return std::rand()%i;}

int deckIdx = 0;

int main(int argc, char** argv) {

	string menu = "Choose number option:\n1. Hit\n2. Stand\n3. Split";
	string one = "1";
	string two = "2";
	string three = "3";
	string hitOptions = "Choose number option:\n1. Hit first hand only\n2. Hit second hand only\n3. Hit both hands";
	string hitChoice; //different choices on what to hit
	
    //create the deck of cards
    string faces[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
    vector<Card> deck;
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 4; j++){
            Card card(faces[i], values[i]);
            deck.push_back(card);
        }
    }
    //shuffles deck
    srand (unsigned (time(0) ) ); // random generator based on time
    random_shuffle ( deck.begin(), deck.end(), randomFunc); // random shuffle
    cout << endl;
    
	double pot;
	double totalBet = 0; //overall amount bet
	double amountWon = 0; //overall earnings
	string play = "Yes";
    string noPlay = "No";
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
		user.hit(deck[deckIdx]); //example dealing, not final
        deckIdx++;
		user.hit(deck[deckIdx]);
        deckIdx++;
		user.seeHand();
		dealer.hit(deck[deckIdx]);
        deckIdx++;
		dealer.hit(deck[deckIdx]);
        deckIdx++;
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
						user.hit(deck[deckIdx]);
                        deckIdx++;
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
							user.hit(deck[deckIdx]);
                            deckIdx++;
							user.seeHand();	
						}
					}
					else if(hitChoice == two){ //hit second hand
						if(user.isDoneSplit()){
							cout<<"You can't hit anymore; you have "<<user.getSplitTotalValue()<<endl;
						}
						else{
							user.hitSplit(deck[deckIdx]);
                            deckIdx++;
							user.seeSplitHand();
						}
					}
					else if(hitChoice == three){ //hit both hands
						if(user.isDone()){
							cout<<"You can't hit anymore in your first hand; you have "<<user.getTotalValue()<<endl;
						}
						else{
							user.hit(deck[deckIdx]);
                            deckIdx++;
							user.seeHand();	
						}
						if(user.isDoneSplit()){
							cout<<"You can't hit anymore in your second hand; you have "<<user.getSplitTotalValue()<<endl;
						}
						else{
                            user.hitSplit(deck[deckIdx]);
                            deckIdx++;
							user.seeSplitHand();
						}
					}
				}
			}
			else if(option == three){ //you want to split when you have duplicate cards
                if(user.splitAble(deckIdx)){
                    isSplit = true;
                    account.bet(pot);
                    totalBet += pot;
                    pot *= 2;
                    cout<<"The pot is now at $"<<pot<<endl;
                    user.hitSplit(deck[deckIdx]);
                    deckIdx++;//example dealing
                    user.hitSplit(deck[deckIdx]);
                    deckIdx++;//according to the instructions, when you split you get two cards to that hand
                    user.seeSplitHand();
                 }else{
                     cout << "You do not a have a pair" << endl;
                 }
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
					dealer.hit(deck[deckIdx]);
                    deckIdx++;//continues to draw until his hand is 17 or above
					cout<<"Dealer hits: "<<deck[deckIdx].getName()<<endl;
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
					dealer.hit(deck[deckIdx++]); //continues to draw until his hand is 17 or above
					cout<<"Dealer hits: "<<deck[deckIdx].getName()<<endl;
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
        
        srand (unsigned (time(0) ) ); // random generator based on time
        random_shuffle ( deck.begin(), deck.end(), randomFunc); // random shuffle
        deckIdx = 0;
        
        if( choice == play && account.getMoney() == 0){
            choice = noPlay;
            cout << "Sorry, you ran out of money! Thanks for playing" << endl;
        }
	}while(choice == play);
	
    if(account.getMoney() != 0) {
        cout<<"Total amount of betting money: $"<<totalBet<<endl;
        cout<<"Total amount won: $"<<amountWon<<endl;
    }
    cout << "Thanks for playing BlackJack!" << endl;
	return 0;
}
