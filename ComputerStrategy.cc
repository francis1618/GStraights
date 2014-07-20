#include "ComputerStrategy.h"
#include "Player.h"
#include <vector>
using namespace std;

//make first valid move, report computer finished with his/her turn
bool ComputerStrategy::executeStrategy(Player& player,  vector<Card>& table) {
	//get possible plays
	vector<Card> choices = validStraightPlays(player, table);
	
	//if there are possible plays, play first possible play
	if(!choices.empty()) {
		player.playCard(choices.front());
		table.push_back(choices.front());

	//else discard first card in hand
	} else {
		player.discard(player.getHand().front());
	}
	return true;
}