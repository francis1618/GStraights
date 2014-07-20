#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

//deck class!!! :D
class Deck {

//output stream overload
friend std::ostream &operator<<(std::ostream &, const Deck &);

public:
	Deck();	//constructor

public:
	void reset();		//reset deck to be in order
	void shuffle();		//shuffle according to given algorithm
	Card deal();		//card dealer
	bool isEmpty() const;	//query if empty

private: 

	int index_;												//index of next card to deal
	const static int CARD_COUNT = Card::SUIT_COUNT * Card::RANK_COUNT;	//number of cards in the deck
	std::vector<Card> cards_;								//vector of cards in the deck
};

//ouput stream overload
std::ostream &operator<<(std::ostream &, const Deck &);

#endif