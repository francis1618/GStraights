#ifndef MODEL_H
#define MODEL_H

#include "Subject.h"
#include "Player.h"
#include "Deck.h"

class Model : public Subject {
public:
	Model();
	~Model();

	void setSeed(int);
	void initGame(char*);
	void beginTurn();
	void processTurn(const Card&);
	void endTurn();
	bool gameOver();

	Player* getCurrentPlayer();
	int getCurrentPlayerNumber();
	std::vector<Card> getTable();

private:
	static const int kNumbeOfPlayers = 4;
	Player* player_[kNumbeOfPlayers];
	std::vector<Card> table_;
	Deck deck_;

	int currentPlayer_;
	int seed_;
	bool newSeed_;
};

#endif