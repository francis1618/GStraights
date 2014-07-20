#ifndef VIEW_H
#define VIEW_H

#include "Observer.h"
#include "CardImage.h"
#include "Model.h"
#include "Controller.h"
#include "CardButton.h"

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/frame.h>
#include <gtkmm/label.h>

class View : public Gtk::Window, public Observer { //:public Observer
public:
	//View(Controller*, Model*);
	View(Model*, Controller*);
	virtual ~View();

public:
	//observer update impl
	void update();

protected:
	//helper functions
	virtual void createNewGame(bool forceCreate = false);
	virtual void displayTurnView();
	virtual void displayEndOfGameStats();
	virtual void displayEndOfRoundStats();

protected:
	//button click event functions
	virtual void strategyToggleButtonClicked(int i);
	virtual void seedButtonClicked();
	virtual void newGameButtonClicked();

private:
	//card image creation delegation
	CardImage &cardUI;

	//overall view
	Gtk::VBox overview;

	//display of cards on table
	Gtk::VBox table_box;
	Gtk::Frame suit_frame[Card::SUIT_COUNT];
	Gtk::HBox suit_display[Card::SUIT_COUNT];
	Gtk::Image card_image[Card::SUIT_COUNT][Card::RANK_COUNT];
	

	Gtk::HBox center_box;
	//display of player's info
	Gtk::Frame player_frame[4];
	Gtk::VBox player_box[4];
	Gtk::Label player_stat[4];
	Gtk::Button strategy_toggle_button[4];	
	//seed and newgame buttons
	Gtk::Button seed_button;
	Gtk::Button new_game_button;

	//user's hand
	Gtk::VBox hand_box;
	Gtk::Label hand_prompt;
	Gtk::HBox hand_select;
	CardButton* hand_button[13];


private:
	Model *model_;
	Controller *controller_;

};

#endif