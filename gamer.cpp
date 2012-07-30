/*
	gamer (human player) model class
	
	(c) roman filippov, 2012
*/
#include <SFML/Window.hpp>
#include <cstdio>
#include "gamer.h"
#include "model.h"
#include "application.h"
#include "options.h"

int Gamer::turn() {
//	int a,b;
//	scanf("%d%d",&a,&b);
//	while(m->app->IsOpened()) {
		sf::Event Event;
		while (m->app->GetEvent(Event)) {
			if (Event.Type == sf::Event::KeyPressed) {
			
				switch (Event.Key.Code) {
					case sf::Key::Up:
				 		moveTo(x-1,y); 
				 		break;
					case sf::Key::Down:
						moveTo(x+1,y);
						break;
					case sf::Key::Left:
						moveTo(x,y-1);
						break;
					case sf::Key::Right:
						moveTo(x,y+1);
						break;
					case sf::Key::Escape:
						return m->view->gameOverScene("Game aborted!");
					default:
						continue;
				}		
				char log_str[30];
				sprintf(log_str,"Gamer moves to: %d %d",x,y);
				m->addLogString(sf::String(log_str));
				
				for(vector<PlayerPtr>::iterator it=m->players.begin()+1; it!=m->players.end(); ++it) {
					if (x == it->get()->getX() && y == it->get()->getY())
						return m->view->gameOverScene("You Lose!");
				}
				
				if (x == m->MAP_SIZE-1 && y == m->MAP_SIZE-1)
					return m->view->gameOverScene("You Win!");
				else 
					return GAME_RUNNING;
			}
		}
		m->app->Display();
		return GAME_RUNNING;
//	}
}

Gamer::Gamer(Model *model,const int &a,const int &b) :Player(model,a,b) {

	player_type = GAME_PLAYER;
};

