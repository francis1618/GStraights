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
	void strategyToggle(int);

	void initGame(char*);
	void endGame();
	bool gameOver() const;

	void initRound();
	void endRound();
	bool roundOver() const;

	void beginTurn();
	void processTurn(const Card&);
	void endTurn();

	Player* getCurrentPlayer();
	int getCurrentPlayerNumber();
	Player** getPlayers();
	std::vector<Card> getTable();
	std::vector<int> getRanking();
	std::vector<int> getWinners();

private:
	static const int kNumbeOfPlayers = 4;
	Player* player_[kNumbeOfPlayers];
	std::vector<Card> table_;
	Deck deck_;
	std::vector<int> ranking_;

	int currentPlayer_;
	int seed_;
	bool newSeed_;
	int roundCountDown_;
	char playerType[4];
};

#endif