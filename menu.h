/*
	menu model class
	
	(c) roman filippov, 2012
*/
#ifndef _MENU_H_
#define _MENU_H_
#include <vector>
#include <string>

#define EXIT_GAME 0
#define NEW_GAME 1
#define GO_OPTIONS 2
#define GO_ABOUT 3
#define GO_HELP 4

using std::vector;
using std::string;

class Menu {
private:
	vector<string> items;
public:
	Menu();
	int show();
	void aboutScene();
	void helpScene();	
};

#endif
