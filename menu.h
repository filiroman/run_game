/*
	menu model class
	
	(c) roman filippov, 2012
*/
#ifndef _MENU_H_
#define _MENU_H_
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "applayer.h"

#define NEW_GAME 0
#define GO_OPTIONS 1
#define GO_MAP_EDITOR 2
#define GO_ABOUT 3
#define GO_HELP 4
#define EXIT_GAME 5

using std::vector;

class Application;

class Menu : public AppLayer {
private:
	vector<sf::String> items;
public:
	Menu(Application *apl);
	Menu(Application *apl, vector<std::string> menuItems);
	int show();
	void aboutScene();
	void helpScene();	
};

#endif
