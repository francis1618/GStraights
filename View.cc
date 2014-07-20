#include "StraightStrategy.h"
#include "View.h"
#include "Misc.h"
#include <gtkmm.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/stock.h>
#include <string>
using namespace std;

View::View(Model *m, Controller *c) 
	: cardUI(CardImage::getInstance()), model_(m), controller_(c){ 
	
	//set up overall view
	set_border_width( 10 );
	add( overview );
	overview.add(table_box);
	overview.add(center_box);
	overview.add(hand_box);

	//set up display for cards on the table
	suit_frame[0].set_label("clubs");
	suit_frame[1].set_label("diamonds");
	suit_frame[2].set_label("hearts");
	suit_frame[3].set_label("spades");
	for(int s=0; s<Card::SUIT_COUNT; s++) {
		for(int r=0; r<Card::RANK_COUNT; r++) {
			card_image[s][r].set(cardUI.getNullCardImage());
			suit_display[s].add(card_image[s][r]);
		}
		suit_frame[s].set_label_align( Gtk::ALIGN_START);
		suit_frame[s].add(suit_display[s]);
		table_box.add(suit_frame[s]);
	}

	//set up display for player's scores, and toggle strategy button
	for(int i=0; i<4; i++) {
		center_box.add(player_frame[i]);
		strategy_toggle_button[i].signal_clicked().connect( sigc::bind<int>( sigc::mem_fun(*this, &View::strategyToggleButtonClicked), i) );
 		player_frame[i].set_label(("player "+itos(i+1)).c_str());
		player_frame[i].set_label_align(Gtk::ALIGN_START);
		player_frame[i].set_shadow_type(Gtk::SHADOW_ETCHED_OUT );
		player_frame[i].add(player_box[i]);
		player_box[i].add(player_stat[i]);
		player_box[i].add(strategy_toggle_button[i]);
	}

	//set up seed and new game buttons
	seed_button.set_label("set seed");
	new_game_button.set_label("new game");
	center_box.add(seed_button);
	center_box.add(new_game_button);
	seed_button.signal_clicked().connect(sigc::mem_fun( *this, &View::seedButtonClicked ));
	new_game_button.signal_clicked().connect(sigc::mem_fun( *this, &View::newGameButtonClicked ));


	//set up display for cards in player's hand
	hand_box.add(hand_prompt);
	hand_prompt.set_alignment(Gtk::ALIGN_START);
	hand_box.add(hand_select);
	//hand select
	for(int i=0; i<13; i++) {
		hand_button[i] = new CardButton(controller_);
		hand_select.add(*((Gtk::Button*)(hand_button[i])));
	}

	//display GTK widgets, connect to model, and start new game
	show_all();
	model_->subscribe(this);
	createNewGame(true);
}


//set new seed
void View::seedButtonClicked() {
    Gtk::Dialog dialog( "Set Random Seed", *this );    
    Gtk::Entry   field;                 
    Gtk::Label   label( "Note: This will only take effect next game" );
    
    Gtk::VBox* contentArea = dialog.get_vbox();
    contentArea->pack_start( label, true, false );
    contentArea->pack_start( field, true, false );
    
    //get rand and shit
    field.set_text( "314159" );
    label.show();
    field.show();
    
    dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    dialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);

	int result = dialog.run();
    std::string seed;
    if(result == Gtk::RESPONSE_OK ) {            
    	seed = field.get_text();
        controller_->setSeed(stoi(seed));
    }
}


//create new game
void View::newGameButtonClicked() {
	createNewGame();
}

//change player strategy type
void View::strategyToggleButtonClicked(int i) {
	Glib::ustring str = strategy_toggle_button[i].get_label();
	if(str == "Computer")
		strategy_toggle_button[i].set_label(" Human ");
	else
		strategy_toggle_button[i].set_label("Computer");
	controller_->strategyToggle(i);
}

//create new game
//if forceCreate is set to true, persist until user accept a arrangement
void View::createNewGame(bool forceCreate ) {

	Gtk::Dialog dialog("Choose Player Type", *this);
	dialog.set_deletable(false);
	Gtk::RadioButton::Group		player[4];
	Gtk::RadioButton*   		choice[4][2];
	
	Gtk::HBox contentArea;
	Gtk::VBox playerArea[4];
	Gtk::Frame playerFrame[4];
	dialog.get_vbox()->add(contentArea);
	
	//query for types of each player(human or computer)
	for(int i=0; i<4; i++) {
		playerFrame[i].set_label("player" + itos(i));

		choice[i][0] = Gtk::manage( new Gtk::RadioButton(player[i],"human") );
		choice[i][1] = Gtk::manage( new Gtk::RadioButton(player[i],"computer") );

		playerArea[i].add( *choice[i][0] );
		playerArea[i].add( *choice[i][1] );
		playerFrame[i].add(playerArea[i]);
		contentArea.add(playerFrame[i]);
	}
	dialog.add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
    dialog.add_button( Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialog.show_all_children();
	

	//create a new game if user presses okay
	//if forceCreate is set, persist until user presses okay
	int result;
	do {
		result = dialog.run();
	   	if(result == Gtk::RESPONSE_OK ) {
			for(int s=0; s<Card::SUIT_COUNT; s++) {
				for(int r=0; r<Card::RANK_COUNT; r++) {
					card_image[s][r].set(cardUI.getNullCardImage());
					card_image[s][r].show();
				}
			}
	   		char type[4];
	   		for(int i=0; i<4; i++) {
	   			if(choice[i][0]->get_active()) {
	   				type[i] = 'h';
	   				strategy_toggle_button[i].set_label(" Human ");
	   			} else { //if(choice[i][1]->get->active())
	   				type[i] = 'c';
	   				strategy_toggle_button[i].set_label("Computer");
	   			}
	   		}		
	    	controller_->newGame(type);
	    	break;
	    } else if(!forceCreate )
	    	break;
	} while (true);

    for(int i=0; i<4; i++)
    	for(int j=0; j<2; j++)
    		delete choice[i][j];
}

//update view
void View::update() {
	vector<Card> table = model_->getTable();

	//update cards on table
	for(int s=0; s<Card::SUIT_COUNT; s++) {
		for(int r=0; r<Card::RANK_COUNT; r++) {
			Card c((Card::Suit)s, (Card::Rank)r);
			if(find(table.begin(), table.end(), c) != table.end())
				card_image[s][r].set(cardUI.getCardImage(c));
			else
				card_image[s][r].set(cardUI.getNullCardImage());
			card_image[s][r].show();
		}
	}

	//update player's score and discard
	for(int i=0; i<4; i++) {
		Player **player = model_->getPlayers();
		string message;
		message += itos(player[i]->getScore()) + " points\n";
		message += itos(player[i]->getDiscard().size()) + " discards";
		player_stat[i].set_text(message);
	}

	//housekeeping
	if(model_->roundOver()) {
		displayEndOfRoundStats();
		if(!model_->gameOver())
			model_->initRound();
		else {
			model_->endGame();
			displayEndOfGameStats();
		}
	} else {
		displayTurnView();
	}
}

//display possible moves in hand
void View::displayTurnView() {
	Player *player = model_->getCurrentPlayer();
	vector<Card> hand = player->getHand();
	vector<Card> choices = StraightStrategy::validStraightPlays(*player, model_->getTable());
	
	//there are valid plays, choices are all valid plays
	//otherwise, choices are to discard anycard in hand
	if(!choices.empty()) {
		hand_prompt.set_text("Player "+itos(model_->getCurrentPlayerNumber()+1)+":  you have valid movies");
	} else {
		hand_prompt.set_text("Player "+itos(model_->getCurrentPlayerNumber()+1)+":  you must discard");
		choices = hand;
	}

	//display all cards in hand, if not a choice, set sensitivity to false
	unsigned i;
	for(i=0; i<hand.size(); i++) {
		if(find(choices.begin(), choices.end(), hand[i]) != choices.end())
			hand_button[i]->setCard(hand[i]);
		else
			hand_button[i]->setCard(hand[i], false);
	}
	for(;i<13; i++)
		hand_button[i]->setNullCard();
}

//display player's discards and total score
void View::displayEndOfRoundStats() {
	Player **player = model_->getPlayers();
	string message;
	for(int p=0; p<4; p++) {
	 	message += "Player " + itos(p+1) + "\'s discards: ";
		vector<Card> discard = player[p]->getDiscard();
		for(unsigned i=0; i<discard.size(); i++) {
			if( 0 < i )
				message += " ";
			message += discard[i].toString();

		}
		message += "\n";
		message += "Player "+itos(p+1)+"\'s score" + itos(player[p]->getScore()) + "\n\n";
	}
	Gtk::MessageDialog dialog(message.c_str());
	dialog.set_title("End of Round");
	dialog.run();
}

//displayer winners
void View::displayEndOfGameStats() {
	for(int i=0; i<13; i++)
		hand_button[i]->setNullCard();

	string message;
	vector<int> winners = model_->getWinners();
	for(unsigned i=0; i<winners.size(); i++)
		message += "Player " + itos(winners[i]+1) + " wins!\n";
	Gtk::MessageDialog dialog(message.c_str());
	//Gtk::Dialog dialog;
	dialog.set_title("End of Game");
	dialog.run();
}

//destructor
View::~View() {
	for(int i=0; i<13; i++)
		delete hand_button[i];
}