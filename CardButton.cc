#include "Card.h"
#include "CardButton.h"

CardButton::CardButton(Controller* c)
	: controller_(c), card_(Card::CLUB, Card::ACE) {
	setNullCard();
	signal_clicked().connect( sigc::mem_fun( *this, &CardButton::cardButtonClicked ) );
}

void CardButton::setCard(const Card &c, bool sensitive) {
	set_sensitive(sensitive);
	card_ = c;
	image_.set(CardImage::getInstance().getCardImage(card_));
	set_image(image_);
}

void CardButton::setNullCard() {
	set_sensitive(false);
	image_.set(CardImage::getInstance().getNullCardImage());
	set_image(image_);
}

void CardButton::cardButtonClicked() {
	controller_->cardClicked(card_);
}