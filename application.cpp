/*
	application model class
	
	(c) roman filippov, 2012
*/
#include <SFML/Window.hpp>
#include <list>
#include "application.h"
#include "model.h"
#include "options.h"
#include "menu.h"
using std::list;

Application::Application() {
	options = new Options();
	menu = new Menu();	
	game = new Model(options);
}

Application::~Application() {
	delete game;
	delete menu;
	delete options;
}

/*void Application::newGame() {
	Model m;																		//in perspective to parallel games
	games.push_back(m);
}*/

void Application::startGame() {
	game->createWorld();
	game->createWalls();
	game->createPlayers(1,1);		//Create 1 real player (don't change!! not implemented yet) 
											//and 1 computer player (may be changed)
	
	while(game->step()) {
		
	}	
}

void Application::run() {
	
	/*while (!games.empty()) 													//Games loop
		for (list<Model>::iterator it = games.begin(); it!= games.end(); ++it)
			if (it->step())
				it = games.erase(it);*/
				
	//Main loop			
	while ((int choose = menu->show()) != EXIT_GAME) {			//show() returns EXIT_GAME (define 0) when user press exit
		switch (choose) :
		{
			case NEW_GAME:
				startGame();
				break;
			case GO_OPTIONS:
				options->optionsScene();
				break;
			case GO_ABOUT:						//cases #defined at menu.h (integer values from 1 to 4)
				menu->aboutScene();
				break;
			case GO_HELP:
				menu->helpScene();
		}
	}	
}
