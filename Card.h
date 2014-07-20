#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

//card class, value based object
class Card{
public:
	friend std::istream &operator>>(std::istream &, Card &);
	enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };			//suit representations
	enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,			//rank representations
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

public:
	Card(Suit, Rank);		//constructor
	Suit getSuit() const;	//getters
	Rank getRank() const;
	std::string toString() const;
	
private:
	Suit suit_;
	Rank rank_;
};

//comparison operators
bool operator==(const Card &, const Card &);
bool operator<(const Card &, const Card &);		//compared first by suit, then by rank

//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

//iostream input overload
#endif
