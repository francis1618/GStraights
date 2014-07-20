#include "Controller.h"

//testing
#include <iostream>
using namespace std;

//constructor
Controller::Controller(Model *m)
	:model_(m) {}

//set seed
void Controller::setSeed(int seed) {
	model_->setSeed(seed);
}

//init new game
void Controller::newGame(char* type) {
	model_->initGame(type);
}

//toggle between human and computer strategy
void Controller::strategyToggle(int p) {
	model_->strategyToggle(p);
}

//report card button clicked
void Controller::cardClicked(const Card &c) {
	model_->processTurn(c);
}