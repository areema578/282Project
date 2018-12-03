#ifndef DECK_H
#define DECK_H
#include <string>
#include <vector>
#include "Card.h"

static const string faces[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
static const int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

class Deck{
	public:
		Deck();
		vector<Card> makeDeck();
};
#endif
