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
	static CardImage& getInstance();		//get singleton instance
	Glib::RefPtr<Gdk::Pixbuf> getCardImage( Card::Suit, Card::Rank ) const;   	// return corresponding image for a card
	Glib::RefPtr<Gdk::Pixbuf> getCardImage( const Card&) const; 			  	
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage() const;                 		// Returns image for a null card

//prohibited functions since this is a singleton
private:
	CardImage();
	CardImage(const CardImage&);
	CardImage& operator=(const CardImage&);

private:
	vector< Glib::RefPtr< Gdk::Pixbuf > > images;                   // Contains the pixel buffer images.
};
#endif