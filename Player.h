#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Card.h"


//forward declaration, no include needed since only pointer is used
class StraightStrategy;

//player class
class Player {
public:
	//constructor and strategy setter
	Player(StraightStrategy*, int);
	~Player();
	void setStrategy(StraightStrategy*);
	void setPlayerNumber(int);
	//modifiers
	void reset(); //because its a reset function and christine realized we needed it
	void addCard(const Card&);
	void playCard(const Card&);		//return false if card is not in hand
	void discard(const Card&); 		//return false if card is not in hand
	void resetDiscard(void);
	void setScore(int); 			//I could have an updateScore where player calculate new score 
									// based on old score and current discards
									// but I wanted to be able to reset player's score to 0 for a new game, 
									// so I settled on setScore
	//accessors
	int getScore() const; 					//get old score
	std::vector<Card> getHand() const;
	std::vector<Card> getDiscard() const;	
	//make a move according to strategy
	bool makeMove(std::vector<Card>&);
private:
	//inner helper function
	void remove(const Card&);

private:
	StraightStrategy *strategy_;	//strategy behaviour
	std::vector<Card> discard_;		//list of discards for the round
	std::vector<Card> hand_;		//list of cards still in hand for the round

	int playerNumber_;
	int score_;						//game score
};


#endif
