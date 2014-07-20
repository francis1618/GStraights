#include "Model.h"
#include "View.h"
#include "Controller.h"
#include <gtkmm.h> 


//EXTRA FEATURE MUSIC
//plays .ogg files in subfolder "music"
//must compile with -DMUSIC
#ifdef MUSIC  
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <dirent.h>
#include <vector>
#include <string>
using namespace std;

//Fork and Execve paradigm
pid_t canberraPID;
void music() {
	//open "music" folder, keep track of all files
	DIR *dir = opendir("music");
	struct dirent *dent;
    vector<string> songs;
    while((dent = readdir(dir)))
        songs.push_back(dent->d_name);
    closedir(dir);
   
   	//if there are no songs, exit
    if(songs.empty())
    	return;

    //infinite loop through all the songs in "music" folder
	vector<string> args;
	args.push_back("canberra-gtk-play");
	args.push_back("-f");
	args.push_back("song.ogg");
	int i = 0;
	while(true) {
		args[2] = "music/"+songs[i];
		pid_t pid = fork();
		if (pid != 0) { 			//parent process wait for child to finish before creating new child
			canberraPID = pid;
		    int status;
		    waitpid(pid, &status, 0);
		} else {					//child plays .ogg file with canberra
			execlp(args[0].c_str(), args[0].c_str(), args[1].c_str(), args[2].c_str(), (char*)0);
		    cerr<<"fatal error, exec returned"<<endl;
		    _exit(EXIT_FAILURE);   // exec never returns
		}
		i = (i+1)%songs.size();
	}

}
#endif


int main( int argc, char ** argv ) {

//another part of the Music extra feature, the music process runs in parallel with Gtk 
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


//kill music process when Gtk is done
#ifdef MUSIC
		kill(pid, SIGKILL);
		kill(canberraPID, SIGKILL);	
	}
#endif

	return 0;
}
