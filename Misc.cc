#include "Misc.h"
#include <sstream>
#include <string>
using namespace std;

string itos(int n) {
	string s;
	stringstream ss;
	ss << n;
	s = ss.str();
	return s;
}

int stoi(string s) {
	int n;
	stringstream ss(s);
	ss >> n;
	return n;
}