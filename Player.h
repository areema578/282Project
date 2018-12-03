#ifndef PLAYER_H
#define PLAYER_H
#include "Card.h"
#include <string>
#include <vector>


using namespace std;

class Player{
	public:
		Player();
		void hit(Card card);
		void hitSplit(Card card);
		void removeHand();
		void removeSplitHand();
		int getTotalValue() const;
		int getSplitTotalValue() const;
		void seeHand();
		void seeSplitHand();
		void seeDealerHand();
		bool isDone();
		bool isDoneSplit();
        bool splitAble(int idx) const;
	private:
		vector<Card> hand;
		vector<Card> splitHand;
		bool done;
		bool doneSplit;
	friend class Card;
};
#endif
