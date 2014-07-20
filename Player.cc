#include <iostream>
#include <vector>
#include <algorithm> 
#include "Player.h"
#include "StraightStrategy.h"
#include <iostream> 
using namespace std;


//constructor, set strategy and player number
Player::Player(StraightStrategy* strategy, int playerNumber)
	: strategy_(strategy), playerNumber_(playerNumber), score_(0) {}


//reset Player info
void Player::reset() {
	hand_.clear();
	discard_.clear();
	score_ = 0;
}

//set player number
void Player::setPlayerNumber(int number) {
	playerNumber_ = number;
}

//update strategy
void Player::setStrategy(StraightStrategy* strategy) {
	if(this->strategy_ && this->strategy_!=strategy)
		delete this->strategy_;
	this->strategy_ = strategy;
}

//add card to hand
void Player::addCard(const Card &card) {
	hand_.push_back(card);
}


//remove card from hand, return true if card is in hand
void Player::playCard(const Card &card) {
	remove(card);
	cout<<"Player "<<playerNumber_<<" plays "<<card<<"."<<endl;
}

//remove card from and and add card to discard pile, return true if card is in hand
void Player::discard(const Card &card) {
	remove(card);
	discard_.push_back(card);
	cout<<"Player "<<playerNumber_<<" discards "<<card<<"."<<endl;

}


//helper function to remove card from hand
void Player::remove(const Card &card) {
    hand_.erase(find(hand_.begin(), hand_.end(), card));

}

//execute strategy
bool Player::makeMove(vector<Card>& table) {
	return strategy_->executeStrategy(*this, table);
}


//get old score
int Player::getScore() const {
	return score_;
}


//set score
void Player::setScore(int score) {
	this->score_ = score;
}

//return copy of hand
vector<Card> Player::getHand() const {
	return hand_;
}


//return copy of discards
vector<Card> Player::getDiscard() const {
	return discard_;
}


//reset discards
void Player::resetDiscard() {
	discard_.clear();
}

//destroy strategy
Player::~Player() {
	if(strategy_)
		delete strategy_;
}
