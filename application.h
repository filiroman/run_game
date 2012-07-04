/*
	application model class
	
	(c) roman filippov, 2012
*/
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include <SFML/Window.hpp>
#include <list>
#include "model.h"
#include "menu.h"
#include "options.h"
using std::list;

class Application: public sf::Window {
private:
	Model *game;
	Menu *menu;
	Options *options;
	//list<Model> games;			//Using list in perspective to many parallel online games (each with menu and options)
public:
	Application();
	~Application();
	//void newGame();
	void run();	
	void startGame();
};

#endif
