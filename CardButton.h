#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include "Controller.h"
#include "Card.h"
#include "CardImage.h"
#include <gtkmm/button.h>
#include <gtkmm/image.h>


//custom button, bind a particular card with clicking event
//also set button appearance to the card
class CardButton : public Gtk::Button {
public:
	//constructor
	CardButton(Controller*);
	//setters
	void setCard(const Card&, bool sensitive = true);
	void setNullCard();
	void cardButtonClicked();
private:
	Controller* controller_;	//bind clicking event to call to controller
	Card card_;					//with card as parameter
	Gtk::Image image_;			//Button image
};

#endif