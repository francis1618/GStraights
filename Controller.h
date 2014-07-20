#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include "Card.h"

//controller class
class Controller {
public:
	Controller(Model*);
	void setSeed(int);	//set seed
	void newGame(char*);	//create new game
	void strategyToggle(int);	//toggle between strategy types
	void cardClicked(const Card&);	//report card button clicked

private:
	Model *model_;
};

#endif 