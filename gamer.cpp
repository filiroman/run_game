/*
	gamer (human player) model class
	
	(c) roman filippov, 2012
*/
#include <SFML/Window.hpp>
#include <cstdio>
#include "gamer.h"
#include "model.h"

bool Gamer::turn() {
//	int a,b;
//	scanf("%d%d",&a,&b);
	sf::Event Event;
	while(1)
	while (m->GetEvent(Event)) {
		
		if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Up))
			moveTo(x+1,y);
		else if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
			moveTo(x,y-1);
		else if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Down))
			moveTo(x-1,y);
		else if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))
			moveTo(x,y+1);
		const sf::Input& Input = m->GetInput();
		if (Input.IsKeyDown(sf::Key::Left)) printf("YEEEAAAAAH\n");
		
//		while (!moveTo(a,b)) {
//			scanf("%d%d",&a,&b);
//		}
		printf("Gamer moves to: %d %d \n",x,y);
		return false; 		//temporarily
	}
}

Gamer::Gamer(Model *model,int a,int b) :Player(model,a,b) {};

