#include "HumanStrategy.h"
#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include <algorithm>
#include <iostream>
using namespace std;


//helper functions
namespace {
	//get string representation of a rank
	string rankStrRepr(Card::Rank r) {
		static string array[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
		return array[r];
	}

	//print cards on table of a particular suit
	void printCardsOfSuit(const vector<Card>& table, Card::Suit suit) {
		if(suit == Card::CLUB) cout<<"Clubs: ";
		else if(suit == Card::DIAMOND) cout<<"Diamonds: ";
		else if(suit == Card::HEART) cout<<"Hearts: ";
		else if(suit == Card::SPADE) cout<<"Spades: ";

		bool firstItem = false;
		for(unsigned i = 0; i<table.size(); i++) {
			if(table[i].getSuit() == suit) {
				if(!firstItem)
					firstItem = true;
				else
					cout<<" ";
				cout<<rankStrRepr(table[i].getRank());
			}
		}
		cout<<endl;
	}
}


//ask user for what to do
bool HumanStrategy::executeStrategy(Player& player, vector<Card>& table) {
	/*
	//find possible plays
	vector<Card>choices = validStraightPlays(player, table);

	//sort and print table
	sort(table.begin(), table.end());
	cout<<"Cards on the table: "<<endl;
	for(unsigned s=0; s<Card::SUIT_COUNT; s++)
		printCardsOfSuit(table, (Card::Suit)s);

	//print hand
	cout<<"Your hand: ";
	const vector<Card>& hand = player.getHand();
	for(unsigned i=0; i<hand.size(); i++) {
		if(0 < i)
			cout<<" ";
		cout<<hand[i];
	}
	cout<<endl;

	//print legal plays
	cout<<"Legal plays: ";
	for(unsigned i=0; i<choices.size(); i++) {
		if(0 < i)
			cout<<" ";
		cout<<choices[i];
	}
	cout<<endl;


	//get human command until a valid play, discard
	Command command;
	while(true) {
		cout<<">";
		cin>>command;
		//if user wants to see deck, print ti
		if(command.type == Command::DECK) {
			cout<<Deck::getInstance()<<endl;

		//if user wants to play cards, check if its valid, is so, play it
		} else if(command.type == Command::PLAY) {
			if(find(choices.begin(), choices.end(), command.card)==choices.end()) {
				cout<<"This is not a legal play."<<endl;
			} else if( player.playCard(command.card)) {
				table.push_back(command.card);
				break;
			}
		//if user wants to discard, check valid plays, if none, discard
		} else if(command.type == Command::DISCARD) {
			if( !choices.empty() )
				cout<<"You have a legal play. You may not discard."<<endl;
			else if(player.discard(command.card))
				break;

		//any other input transfer control back to game
		} else {
			throw InvalidHumanStrategyException(command);		
		}
	}*/
	return false;
}