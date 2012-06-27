/*
	menu model class
	
	(c) roman filippov, 2012
*/
#ifndef _MENU_H_
#define _MENU_H_
#include <vector>
#include <string>
using std::vector;
using std::string;

class Menu {
private:
	vector<string> items;
public:
	Menu();
	bool show();
	
};

#endif
