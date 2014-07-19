#include "StraightStrategy.h"
#include "View.h"
#include "Misc.h"
#include <gtkmm.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/stock.h>

View::View(Model *m, Controller *c) 
	: cardUI(CardImage::getInstance()), model_(m), controller_(c){ 
	set_border_width( 10 );
	add( overview );
	overview.add(table_frame);
	overview.add(user_input);

	//table
	table_frame.set_label("table");
	table_frame.set_label_align( Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP );
	table_frame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	table_frame.set_border_width( 20 );
	table_frame.add(table_display);
	
	for(int s=0; s<Card::SUIT_COUNT; s++) {
		for(int r=0; r<Card::RANK_COUNT; r++) {
			card_image[s][r].set(cardUI.getNullCardImage());
			suit_display[s].add(card_image[s][r]);
		}
		table_display.add(suit_display[s]);
	}


	//user input
	user_input.add(hand_select);
	user_input.add(other_select);

	//hand select
	for(int i=0; i<13; i++) {
		hand_button[i] = new CardButton(controller_);
		hand_select.add(*((Gtk::Button*)(hand_button[i])));
	}


	//other select
	other_select.add(rageQuit);
	other_select.add(gameQuit);
	other_select.add(newGame);


	//other misc buttons and boxes
	overview.add(seedButton);
	overview.add(newGameButton);
	seedButton.signal_clicked().connect(sigc::mem_fun( *this, &View::seedButtonClicked ));
	newGameButton.signal_clicked().connect(sigc::mem_fun( *this, &View::newGameButtonClicked ));

	//display GTK
	show_all();
	model_->subscribe(this);

	createNewGame(true);
}

void View::seedButtonClicked() {
    Gtk::Dialog dialog( "Set Random Seed", *this );    
    Gtk::Entry   field;                 
    Gtk::Label   label( "Note: This will only take effect next game" );
    
    // Add the text entry widget to the dialog box.
    // Add the text entry widget to the vertical box section of the dialog box.
    Gtk::VBox* contentArea = dialog.get_vbox();
    contentArea->pack_start( label, true, false );
    contentArea->pack_start( field, true, false );
    
    //get rand and shit
    field.set_text( "1234" );
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

void View::newGameButtonClicked() {
	createNewGame();
}

void View::createNewGame(bool forceCreate ) {
	
	Gtk::Dialog dialog("Choose Player Type", *this);
	dialog.set_deletable(false);
	Gtk::RadioButton::Group		player[4];
	Gtk::RadioButton*   		choice[4][2];
	
	Gtk::HBox contentArea;
	Gtk::VBox playerArea[4];
	Gtk::Frame playerFrame[4];
	dialog.get_vbox()->add(contentArea);
	
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
	

	int result;
	do {
		result = dialog.run();
	   	if(result == Gtk::RESPONSE_OK ) {
	   		char type[4];
	   		for(int i=0; i<4; i++) {
	   			if(choice[i][0]->get_active())
	   				type[i] = 'h';
	   			else //if(choice[i][1]->get->active())
	   				type[i] = 'c';
	   		}
	    	controller_->newGame(type);
	    	break;
	    }
	} while (true);

    for(int i=0; i<4; i++)
    	for(int j=0; j<2; j++)
    		delete choice[i][j];
}

void View::update() {
	Player *player = model_->getCurrentPlayer();
	vector<Card> choices = StraightStrategy::validStraightPlays(*player, model_->getTable());
	if(choices.empty())
		choices = player->getHand();

	unsigned i;
	for(i=0; i<choices.size(); i++)
		hand_button[i]->setCard(choices[i]);
	for(;i<13; i++)
		hand_button[i]->setNullCard();
}

View::~View() {
	for(int i=0; i<13; i++)
		delete hand_button[i];
}