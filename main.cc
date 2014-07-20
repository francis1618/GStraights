#include "Model.h"
#include "View.h"
#include "Controller.h"
#include <gtkmm.h> 

#ifdef MUSIC  

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <dirent.h>
#include <vector>
#include <string>
using namespace std;

pid_t canberraPID;
void music() {

	DIR *dir = opendir("music");
	struct dirent *dent;
    vector<string> songs;
    while((dent = readdir(dir)))
        songs.push_back(dent->d_name);
    closedir(dir);
   
    if(songs.empty())
    	return;

	vector<string> args;
	args.push_back("canberra-gtk-play");
	args.push_back("-f");
	args.push_back("song.ogg");

	int i = 0;
	while(true) {
		args[2] = "music/"+songs[i];
		pid_t pid = fork();
		if (pid != 0) { //parent
			canberraPID = pid;
		    int status;
		    waitpid(pid, &status, 0);
		} else {
			execlp(args[0].c_str(), args[0].c_str(), args[1].c_str(), args[2].c_str(), (char*)0);
		    cerr<<"fatal error, exec returned"<<endl;
		    _exit(EXIT_FAILURE);   // exec never returns
		}
		i = (i+1)%songs.size();
	}

}
#endif

int main( int argc, char ** argv ) {

#ifdef MUSIC
	pid_t pid = fork();
	if(pid == 0) {
		while(true)
			music();
	} else {
#endif
		//init gtkmm
		Gtk::Main   kit( argc, argv );          
		//create model, view controller
		Model model;
		Controller controller(&model);
		View view(&model, &controller);
		//run program
		Gtk::Main::run( view );

#ifdef MUSIC
		kill(pid, SIGKILL);
		kill(canberraPID, SIGKILL);	
	}
#endif
	return 0;
}
