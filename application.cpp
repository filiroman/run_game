/*
	application model class
	
	(c) roman filippov, 2012
*/
#include <cstdio>
#include "application.h"
#include "model.h"
#include "options.h"
#include "menu.h"

Application::Application() {
	options = new Options(this);
	menu = new Menu(this);	
	Settings *st = options->getSettings();
	sf::Window::Create(sf::VideoMode::GetMode(st->resolution), GAME_WINDOW_NAME, st->fullscreen ? sf::Style::Fullscreen : sf::Style::Resize|sf::Style::Close);
}

Application::~Application() {
	delete menu;
	delete options;
}

/*void Application::newGame() {
	Model m;																		//in perspective to parallel games
	games.push_back(m);
}*/

bool Application::startGame() {
	printf("Starting game\n");
	
	game = new Model(this,options);

	int ai_num = options->getSettings()->enemies;	
		
	game->createWorld();
	game->createWalls();
	game->createPlayers(ai_num);		//Create 1 computer player (real player is also 1 now);
	
	while (!(game->checkPaths())) {		//checking path availability of every player
		game->createWalls();
		game->createPlayers(ai_num);
	}
	
	printf("Let's Go!\n");
											
	int choose = game->step();
	delete game;	
	
	return !(static_cast<bool>(choose));
}

void Application::run() {
	
	/*while (!games.empty()) 													//Games loop
		for (list<Model>::iterator it = games.begin(); it!= games.end(); ++it)
			if (it->step())
				it = games.erase(it);*/
				
	int choose;			
	//Main loop			
	while ((choose = menu->show()) != EXIT_GAME) {			//show() returns EXIT_GAME (define 0) when user press exit
		switch (choose)
		{
			case NEW_GAME:
				while(startGame());
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
