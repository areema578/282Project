#include "Deck.h"

Deck::Deck(){
	
}

vector<Card> Deck::makeDeck(){
	vector<Card> deck;
	for(int i = 0; i < 13; i++){
		for(int j = 0; j < 4; j++){
			Card card(faces[i], values[i]);
			deck.push_back(card);
		}
	}
	return deck;
}
