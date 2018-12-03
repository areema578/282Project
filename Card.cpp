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
#include "Card.h"

Card::Card(string cardName, int value){
	this->cardName = cardName;
	this->value = value;
}

string Card::getName() const {
	return cardName;
}

int Card::getValue() const {
	return value;
}

void Card::setValue(int value){
	this->value = value;
}
