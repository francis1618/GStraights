#include "Deck.h"
#include "Card.h"
#include "Model.h"
#include "Player.h"
#include "StraightStrategy.h"
#include "HumanStrategy.h"
#include "ComputerStrategy.h"
#include <cstdlib>
#include <vector>
using namespace std;

Model::Model() 
	:  seed_(0), newSeed_(true) {
	for(int i=0; i<kNumbeOfPlayers; i++)
		player_[i] = NULL;
}

void Model::setSeed(int seed) {
	seed_ = seed;
	newSeed_ = true;
}

void Model::initGame(char playerType[4]) {
	//create players
	for(int i=0; i<kNumbeOfPlayers; i++) {
		//create strategy
		StraightStrategy *strategy;
		if(playerType[i] == 'h')
			strategy = new HumanStrategy;
		else //if (playerType[i]== 'c')
			strategy = new ComputerStrategy;

		//create player with strategy
		if(NULL == player_[i])
			player_[i] = new Player(strategy);	
		else
			player_[i]->setStrategy(strategy);
	
		//reset player's score
		player_[i]->setScore(0);
	}

	//seed if needed
	if(newSeed_) {
		srand48(seed_);
		newSeed_ = false;
	}


	//deal cards, find firstPlayer of the round
	deck_.shuffle();
	Card startCard(Card::SPADE, Card::SEVEN);
	for(int i=0; i<kNumbeOfPlayers; i++) {
		for(int j=0; j<Card::SUIT_COUNT*Card::RANK_COUNT/kNumbeOfPlayers; j++) {
			Card card = deck_.deal();
			if(card == startCard)
				currentPlayer_ = i;
			player_[i]->addCard(card);
		}
	}

	//clear table
	table_.clear();
	beginTurn();
}

//mutual tail recursion with endTurn
void Model::beginTurn() {
	bool finished = getCurrentPlayer()->makeMove(table_);
	if(finished)
		endTurn();
	notify();

}

void Model::processTurn(const Card& c) {
	Player *p = getCurrentPlayer();

	vector<Card> choices = StraightStrategy::validStraightPlays(*p, table_);
	if(!choices.empty()) {
		p->playCard(c);
		table_.push_back(c);
	} else {
		p->discard(c);
	}
	endTurn();
}

//mutual tail recursion iwth beginTurn
void Model::endTurn() {
	if(!gameOver()) {
		currentPlayer_ = (currentPlayer_+1)%kNumbeOfPlayers;
		beginTurn();
	}
}


bool Model::gameOver() {
	for(int i=0; i<kNumbeOfPlayers; i++)
		if(80<=player_[i]->getScore())
			return true;
	return false;
}

Player* Model::getCurrentPlayer() {
	return player_[getCurrentPlayerNumber()];
}

int Model::getCurrentPlayerNumber() {
	return currentPlayer_;
}

vector<Card> Model::getTable() {
	return table_;
}

Model::~Model() {
	for(int i=0; i<kNumbeOfPlayers; i++)
		delete player_[i];
}