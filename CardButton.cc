#include "Card.h"
#include "CardButton.h"

//constructor, default to null card
CardButton::CardButton(Controller* c)
	: controller_(c), card_(Card::CLUB, Card::ACE) {
	setNullCard();
	signal_clicked().connect( sigc::mem_fun( *this, &CardButton::cardButtonClicked ) );
}

//set card and sensitivity
void CardButton::setCard(const Card &c, bool sensitive) {
	set_sensitive(sensitive);
	card_ = c;
	image_.set(CardImage::getInstance().getCardImage(card_));
	set_image(image_);
}

//set null card, forced not sensitive
void CardButton::setNullCard() {
	set_sensitive(false);
	image_.set(CardImage::getInstance().getNullCardImage());
	set_image(image_);
}

//notify controller of clicking event and card clicked
void CardButton::cardButtonClicked() {
	controller_->cardClicked(card_);
}