/*
	menu model class
	
	(c) roman filippov, 2012
*/
//#include <string>
#include <cstdio>
#include "menu.h"

Menu::Menu() {
	items.push_back("New Game");
	items.push_back("Settings");
	items.push_back("About");
	items.push_back("Help");
	items.push_back("Exit");
}

int Menu::show() {
	for(vector<string>::iterator it = items.begin(); it!= items.end(); ++it)
		printf("%s\n",it->c_str());
	int res;
	scanf("%d",&res);
	return res;		
}

void Menu::aboutScene() {
	printf("About!\n");
}

void Menu::helpScene() {
	printf("Help!\n");
}
