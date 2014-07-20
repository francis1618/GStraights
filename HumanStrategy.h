#ifndef HUMANSTRATEGY_H
#define HUMANSTRATEGY_H

#include "StraightStrategy.h"
#include <vector>

//Huamn Straight Strategy
class HumanStrategy : public StraightStrategy {
public:
	bool executeStrategy(Player&, std::vector<Card>&);
};

#endif