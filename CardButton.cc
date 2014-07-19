#include "Card.h"
#include "CardButton.h"

CardButton::CardButton(Controller* c)
	: controller_(c), card_(Card::CLUB, Card::ACE) {
	setNullCard();
	signal_clicked().connect( sigc::mem_fun( *this, &CardButton::cardButtonClicked ) );
}

void CardButton::setCard(const Card &c) {
	nullState_ = false;
	card_ = c;
	image_.set(CardImage::getInstance().getCardImage(card_));
	set_image(image_);
}

void CardButton::setNullCard() {
	nullState_ = true;
	image_.set(CardImage::getInstance().getNullCardImage());
	set_image(image_);
}

void CardButton::cardButtonClicked() {
	if(!nullState_)
		controller_->cardClicked(card_);
}