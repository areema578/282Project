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
