/*
	view model class
	
	(c) roman filippov, 2012
*/
#include <SFML/Graphics.hpp>
//#include <cstdio>
#include "view.h"
#include "application.h"

View::View(Application *apl) :app(apl) {};

int View::gameOverScene(const std::string &s) {
	
	sf::String GameOver(s+"\nRetry?");
	GameOver.SetFont(sf::Font::GetDefaultFont());
	GameOver.SetColor(sf::Color(0, 128, 128));
	GameOver.SetPosition(app->GetWidth()/2, app->GetHeight()/2);
	GameOver.SetSize(50.f);
	
	sf::String Yes("Yes/"), No("No");
	Yes.SetFont(sf::Font::GetDefaultFont());
	Yes.SetColor(sf::Color(0, 128, 128));
	Yes.SetPosition(GameOver.GetPosition().x, GameOver.GetPosition().y + GameOver.GetRect().GetHeight());
	Yes.SetSize(50.f);
	
	No.SetFont(sf::Font::GetDefaultFont());
	No.SetColor(sf::Color(0, 128, 128));
	No.SetPosition(GameOver.GetPosition().x + Yes.GetRect().GetWidth(), GameOver.GetPosition().y + GameOver.GetRect().GetHeight());
	No.SetSize(50.f);
	
	app->Draw(GameOver);
	app->Draw(Yes);
	app->Draw(No);
	
	app->Display();
	
	while(app->IsOpened()) {
		sf::Event Event;
		while (app->GetEvent(Event)) {
			if (Event.Type == sf::Event::MouseButtonPressed) { 
					if (Yes.GetRect().Contains(Event.MouseButton.X,Event.MouseButton.Y))
						return GAME_ENDED_RETRY;
					if (No.GetRect().Contains(Event.MouseButton.X,Event.MouseButton.Y))
						return GAME_ENDED_NO_RETRY;
			}				
		}
	}	

//	printf("Game over! \n %s \n Retry? (1/0)",s.c_str());
//	int m;
//	scanf("%d",&m);

//	return m ? GAME_ENDED_RETRY : GAME_ENDED_NO_RETRY;
}
