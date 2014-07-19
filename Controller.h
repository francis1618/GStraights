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
	void cardClicked(const Card&);

private:
	Model *model_;
};

#endif 