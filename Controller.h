#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include "Card.h"

class Controller {
public:
	Controller(Model*);
	//void newGameClicked();
	void setSeed(int);
	void newGame(char*);
	void strategyToggle(int);
	void cardClicked(const Card&);

private:
	Model *model_;
};

#endif 