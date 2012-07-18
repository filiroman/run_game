/*
	gamer (human player) model class
	
	(c) roman filippov, 2012
*/
#include <SFML/Window.hpp>
#include <cstdio>
#include "gamer.h"
#include "model.h"
#include "application.h"

int Gamer::turn() {
//	int a,b;
//	scanf("%d%d",&a,&b);
	while(m->app->IsOpened()) {
		sf::Event Event;
		while (m->app->GetEvent(Event)) {
			if (Event.Type == sf::Event::KeyPressed) {
			
				switch (Event.Key.Code) {
					case sf::Key::Up:
				 		moveTo(x+1,y); 
				 		break;
					case sf::Key::Down:
						moveTo(x-1,y);
						break;
					case sf::Key::Left:
						moveTo(x,y-1);
						break;
					case sf::Key::Right:
						moveTo(x,y+1);
						break;
					default:
						continue;
				}		
				printf("Gamer moves to: %d %d \n",x,y);
				return 1;
			}
		}
		m->app->Display();
	}
}

Gamer::Gamer(Model *model,int a,int b) :Player(model,a,b) {

	player_type = GAME_PLAYER;
};

