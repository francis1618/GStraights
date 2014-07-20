#ifndef MISC_H
#define MISC_H

#include <string>

//utility function for converting between int and std::string
//uses sstream to do the conversion

std::string itos(int); //integer to string conversion
int stoi(std::string);	//string to integer conversion
#endif
