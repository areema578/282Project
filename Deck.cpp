#include "Deck.h"

Deck::Deck(){
	index = -1;
	for(int i = 0; i < 13; i++){ //all type of cards
		for(int j = 0; j < 4; j++){ //four of each card
			Card card(faces[i], values[i]);
			deck.push_back(card);
		}
	}
}

vector<Card> Deck::getDeck(){
	return deck;
}


int Deck::getIndex(){
	return index;
}

void Deck::incrementIndex(){
	index++;
}

