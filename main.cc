#include "Model.h"
#include "View.h"
#include "Controller.h"
#include <gtkmm.h>           

int main( int argc, char ** argv ) {
	//init gtkmm
	Gtk::Main   kit( argc, argv );          
	
	//create model, view controller
	Model model;
	Controller controller(&model);
	View view(&model, &controller);
	
	//run program
	Gtk::Main::run( view );
	
	return 0;
}