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

//constructor
Model::Model() 
	:  seed_(0), newSeed_(true) {
	for(int i=0; i<kNumbeOfPlayers; i++)
		player_[i] = NULL;
}

//set new seed
void Model::setSeed(int seed) {
	seed_ = seed;
	newSeed_ = true;
}

//toggle between human and computer strategy for the player
void Model::strategyToggle(int p) {
	if(playerType[p] == 'h') {
		player_[p]->setStrategy(new ComputerStrategy);
		playerType[p] = 'c';
		if(p == currentPlayer_) { 
			getCurrentPlayer()->makeMove(table_);
			endTurn();
		}
	} else {
		player_[p]->setStrategy(new HumanStrategy);
		playerType[p] = 'h';
	}
}


//game initilization
void Model::initGame(char type[]) {
	for(int i=0; i<kNumbeOfPlayers; i++)
		playerType[i] = type[i];
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
			player_[i] = new Player(strategy, i+1);	
		else
			player_[i]->setStrategy(strategy);
	
		//reset player's Christine
		player_[i]->reset();
	}

	//seed if needed
	if(newSeed_) {
		srand48(seed_);
		newSeed_ = false;
		deck_.reset();
	}
	table_.clear();
	initRound();
}

//round initilization
void Model::initRound() {
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
	cout<<"A new round begins. It's player "<<currentPlayer_+1<<"\'s turn to play."<<endl;
	roundCountDown_ = 52;
	table_.clear();
	for(int p=0; p<kNumbeOfPlayers; p++)
		player_[p]->resetDiscard();
	beginTurn();
}

//round cleanup
void Model::endRound() {
	for(int p=0; p<kNumbeOfPlayers; p++) {
		int roundScore = 0;;

		cout<<"Player "<<p+1<<"\'s discards: ";
		vector<Card> discard = player_[p]->getDiscard();
		for(unsigned i=0; i<discard.size(); i++) {
			if( 0 < i )
				cout<<" ";
			cout<<discard[i];
			roundScore += (discard[i].getRank()+1);
		}
		cout<<endl;

		//output each player's old scores and round score and new score
		int newScore = player_[p]->getScore() + roundScore;
		cout<<"Player "<<p+1<<"\'s score: "<<player_[p]->getScore()<<" + "<<roundScore<<" = "<<newScore<<endl;

		//update player's scores
		player_[p]->setScore(newScore);
	}
	notify();
}

//check if round is over
bool Model::roundOver() const {
	return 0 == roundCountDown_;
}

//game cleanup
void Model::endGame() {
	//can't just sort on ranking because has to have secondary ordering based on player#
	ranking_.clear();
	for(int i=0; i<kNumbeOfPlayers; i++)
		ranking_.push_back(i);

	for(int i=0; i<kNumbeOfPlayers-2; i++) {
		for(int j=0; j<kNumbeOfPlayers-1; j++) {
			if( player_[ranking_[j]]->getScore() > player_[ranking_[j+1]]->getScore() ) {
				int temp = ranking_[j];
				ranking_[j]=ranking_[j+1];
				ranking_[j+1]=temp;
			}
		}
	}

	vector<int> winners = getWinners();
	for(unsigned i=0; i<winners.size(); i++)
		cout<<"Player "<<winners[i]+1<<" wins!"<<endl;
}


//get player in order of their scores
vector<int> Model::getRanking() const {
	return ranking_;
}

//get winners(possible tied and multiple)
vector<int> Model::getWinners() const {
	vector<int> winners;
	winners.push_back(ranking_[0]);
	for(unsigned i=1; player_[ranking_[i]]->getScore() == player_[winners[0]]->getScore(); i++)
		winners.push_back(ranking_[i]);
	return winners;

}

//mutual tail recursion with endTurn
//begin a turn
void Model::beginTurn() {
	roundCountDown_--;
	bool finished = getCurrentPlayer()->makeMove(table_);
	if(finished)
		endTurn();
	else
		notify();

}

//process ui info, and end the turn
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
//end turn cleanup
void Model::endTurn() {
	if(roundCountDown_ == 0) {
		endRound();
	} else {
		currentPlayer_ = (currentPlayer_+1)%kNumbeOfPlayers;
		beginTurn();
	}
}


//check if a player has over 80 score
bool Model::gameOver() const {
	for(int i=0; i<kNumbeOfPlayers; i++)
		if(80<=player_[i]->getScore())
			return true;
	return false;
}

//getters
Player* Model::getCurrentPlayer() const {
	return player_[currentPlayer_];
}

int Model::getCurrentPlayerNumber() const {
	return currentPlayer_;
}

Player** Model::getPlayers() {//const {
	return player_;
}

vector<Card> Model::getTable() const {
	return table_;
}

Model::~Model() {
	for(int i=0; i<kNumbeOfPlayers; i++)
		delete player_[i];
}