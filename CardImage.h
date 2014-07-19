#ifndef CARD_GUI_H
#define CARD_GUI_H
#include "Card.h"
#include <gdkmm/pixbuf.h>
#include <vector>
using std::vector;


//this is a singleton because there is absolutely no reason
//for having more than one of this class, this class is just a
//utility for getting image of a card
class CardImage {

public:
	static CardImage& getInstance();
	Glib::RefPtr<Gdk::Pixbuf> getCardImage( Card::Suit, Card::Rank );   // Returns the image for the specified card.
	Glib::RefPtr<Gdk::Pixbuf> getCardImage( const Card&); 
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();                 // Returns the image to use for the placeholder.

//prohibited
private:
	CardImage();
	CardImage(const CardImage&);
	CardImage& operator=(const CardImage&);

private:
	vector< Glib::RefPtr< Gdk::Pixbuf > > images;                   // Contains the pixel buffer images.
};
#endif