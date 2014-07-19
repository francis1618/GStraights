#ifndef STRAIGHTSTRATEGY_H
#define STRAIGHTSTRATEGY_H

#include <vector>

//forward declaration since only pointers are needed
class Card;
class Player;

//strategy pattern base class
class StraightStrategy {
public:
	//strategy template and virtual destructor
	virtual bool executeStrategy(Player&, std::vector<Card>&) = 0;
	virtual ~StraightStrategy();

public:
	//embedding the rules of Straight into the Strategy class
	//potentially the Game class and choose between different types of games by
	//using different strategy hierarchies
	static std::vector<Card> validStraightPlays(const Player&, const std::vector<Card>&);
};

#endif