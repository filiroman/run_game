/*
	menu model class
	
	(c) roman filippov, 2012
*/
//#include <string>
#include <vector>
#include "menu.h"
//using std::string;
using std::vector;

Menu::Menu() {
	items.push_back("New Game");
	items.push_back("Settings");
	items.push_back("About");
	items.push_back("Help");
	items.push_back("Exit");
}

bool Menu::show() {
	//User interacting actions, return true if exit is pressed;
}
