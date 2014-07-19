#include "Controller.h"

//testing
#include <iostream>
using namespace std;

Controller::Controller(Model *m)
	:model_(m) {}

void Controller::setSeed(int seed) {
	model_->setSeed(seed);
}

void Controller::newGame(char* type) {
	model_->initGame(type);
}

void Controller::cardClicked(const Card &c) {
	model_->processTurn(c);
}