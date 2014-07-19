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

class View : public Gtk::Window, public Observer { //:public Observer
public:
	//View(Controller*, Model*);
	View(Model*, Controller*);
	virtual ~View();

public:
	void update();

protected:
	//card image delegation
	CardImage &cardUI;

	//overall view
	Gtk::VBox overview;

	//display of cards on table
	Gtk::VBox table_display;
	Gtk::Frame table_frame;
	Gtk::HBox suit_display[Card::SUIT_COUNT];
	Gtk::Image card_image[Card::SUIT_COUNT][Card::RANK_COUNT];
	

	//user interaction
	Gtk::HBox user_input;
	//user's hand
	Gtk::HBox hand_select;
	CardButton* hand_button[13];
	//other input
	Gtk::VBox other_select;
	Gtk::Button rageQuit;
	Gtk::Button gameQuit;
	Gtk::Button newGame;

	//other misc widgets and boxes
	Gtk::Button seedButton;
	Gtk::Button newGameButton;
	virtual void seedButtonClicked();
	virtual void newGameButtonClicked();
	virtual void createNewGame(bool forceCreate = false);
private:
	Model *model_;
	Controller *controller_;

};

#endif