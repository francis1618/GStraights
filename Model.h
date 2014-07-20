#ifndef MODEL_H
#define MODEL_H

#include "Subject.h"
#include "Player.h"
#include "Deck.h"


//model class, implements the Subject interface
class Model : public Subject {
public:
	//constructor, destructor
	Model();
	~Model();

	//setters
	void setSeed(int);
	void strategyToggle(int);

	//create game, clean up game, check if game is over
	void initGame(char*);
	void endGame();
	bool gameOver() const;

	//create round, clean up round, check if round is over
	void initRound();
	void endRound();
	bool roundOver() const;

	//start turn, process ui info, end turn
	void beginTurn();
	void processTurn(const Card&);
	void endTurn();

	//getters
	Player* getCurrentPlayer() const;
	int getCurrentPlayerNumber() const;
	Player** getPlayers();	//cannot be const because returning non const pointer that are member
	std::vector<Card> getTable() const;
	std::vector<int> getRanking() const;
	std::vector<int> getWinners() const;

//member functions
private:
	static const int kNumbeOfPlayers = 4;
	Player* player_[kNumbeOfPlayers];
	std::vector<Card> table_;
	Deck deck_;
	std::vector<int> ranking_;

	int currentPlayer_;
	int seed_;
	bool newSeed_;	//indicate if a new seed has been check for next game
	int roundCountDown_; //indicate how many more turns are in the current round
	char playerType[4]; //indiate player's strategy type
};

#endif