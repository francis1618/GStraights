#include "CardImage.h"
#include "Misc.h"
#include <algorithm>
#include <iterator>
#include <string>

#include <iostream>

using namespace std;

// Loads the image from the specified file name into a pixel buffer.
Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string &name) {
	return Gdk::Pixbuf::create_from_file( name );
} // createPixbuf

CardImage& CardImage::getInstance() {
	static CardImage ci;
	return ci;
}

CardImage::CardImage()  {
	vector<string> image_names;
	for(int s=0; s<Card::SUIT_COUNT; s++) {
		for(int r=0; r<Card::RANK_COUNT; r++) {
			string name = "cardImages/" + itos(s) + "_" + itos(r) + ".png";
			image_names.push_back(name);
		}
	}
	image_names.push_back("cardImages/null.png");

	for(unsigned i=0; i<image_names.size(); i++)
		images.push_back(createPixbuf(image_names[i]));
}

// Returns the image for the specified card.
Glib::RefPtr<Gdk::Pixbuf> CardImage::getCardImage( Card::Suit s, Card::Rank r ) {
	int index = (s)*Card::RANK_COUNT + (r);
	return images[ index ];
}

Glib::RefPtr<Gdk::Pixbuf> CardImage::getCardImage( const Card& card) {
	return getCardImage(card.getSuit(), card.getRank());
}


// Returns the image to use for the placeholder.
Glib::RefPtr<Gdk::Pixbuf> CardImage::getNullCardImage() {
	int size = images.size();
	return images[ size-1 ];
}