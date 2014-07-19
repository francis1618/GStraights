#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include "Controller.h"
#include "Card.h"
#include "CardImage.h"
#include <gtkmm/button.h>
#include <gtkmm/image.h>

class CardButton : public Gtk::Button {
public:
	CardButton(Controller*);
	void setCard(const Card&);
	void setNullCard();
	void cardButtonClicked();
private:
	Controller* controller_;
	Card card_;
	Gtk::Image image_;
	bool nullState_;

};

#endif