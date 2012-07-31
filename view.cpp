/*
	view model class
	
	(c) roman filippov, 2012
*/
#include <SFML/Graphics.hpp>
//#include <cstdio>
#include "view.h"
#include "application.h"
#include "model.h"
#include "options.h"

View::View(Application *apl) : AppLayer(apl) {};

void View::menuDraw() const {
	
	app->Clear();

	sf::Image timg;
	timg.LoadFromFile(GAME_RESOURCES(player_game.png));
	sf::Sprite test(timg);
	test.SetPosition(100,100);
	
	sf::Image timg2;
	timg2.LoadFromFile(GAME_RESOURCES(box_game.png));
	sf::Sprite test2(timg2);
	test2.SetPosition(100,100);
	test2.Rotate(90);
	
	sf::Image timg3;
	timg3.LoadFromFile(GAME_RESOURCES(computer_game.png));
	sf::Sprite test3(timg3);
	test3.SetPosition(100,100);
	test3.Rotate(180);

	sf::Image timg4;
	timg4.LoadFromFile(GAME_RESOURCES(box_game.png));
	sf::Sprite test4(timg4);
	test4.SetPosition(100,100);
	test4.Rotate(-90);
	
	app->Draw(sf::Shape::Rectangle(test.GetPosition().x-test.GetSubRect().GetWidth()*1.5, test.GetPosition().y+test.GetSubRect().GetHeight()+4, app->GetWidth()-test.GetPosition().x+test.GetSubRect().GetWidth()*1.5, test.GetPosition().y+test.GetSubRect().GetHeight()+6, sf::Color::Color(100,100,100)));
	
	app->Draw(sf::Shape::Rectangle(test.GetPosition().x+test.GetSubRect().GetWidth()+4, test.GetPosition().y-test.GetSubRect().GetHeight()*1.5, test.GetPosition().x+test.GetSubRect().GetWidth()+6, app->GetHeight()-test.GetPosition().y+test.GetSubRect().GetHeight()*1.5, sf::Color::Color(100,100,100)));
	
	app->Draw(test);	
	app->Draw(test2);
	app->Draw(test3);
	app->Draw(test4);
	app->Display();
	
}

int View::gameOverScene(const std::string &s) const {
	
	app->Display();
	
	sf::String GameOver(s+"\nRetry?");
	GameOver.SetFont(sf::Font::GetDefaultFont());
	GameOver.SetColor(sf::Color(0, 128, 128));
	GameOver.SetPosition(app->GetWidth()/2, app->GetHeight()/2);
	GameOver.SetSize(FONT_SIZE);
	
	sf::String Yes("Yes/"), No("No");
	Yes.SetFont(sf::Font::GetDefaultFont());
	Yes.SetColor(sf::Color(0, 128, 128));
	Yes.SetPosition(GameOver.GetPosition().x, GameOver.GetPosition().y + GameOver.GetRect().GetHeight());
	Yes.SetSize(FONT_SIZE);
	
	No.SetFont(sf::Font::GetDefaultFont());
	No.SetColor(sf::Color(0, 128, 128));
	No.SetPosition(GameOver.GetPosition().x + Yes.GetRect().GetWidth(), GameOver.GetPosition().y + GameOver.GetRect().GetHeight());
	No.SetSize(FONT_SIZE);
	
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
