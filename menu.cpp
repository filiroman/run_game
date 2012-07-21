/*
	menu model class
	
	(c) roman filippov, 2012
*/
//#include <string>
#include <SFML/Graphics.hpp>
#include <cstdio>
#include "application.h"
#include "menu.h"
#include "model.h"

Menu::Menu(Application *apl) {

	app = apl;

	items.push_back(sf::String("New Game"));
	items.push_back(sf::String("Settings"));
	items.push_back(sf::String("About"));
	items.push_back(sf::String("Help"));
	items.push_back(sf::String("Exit"));
}

int Menu::show() {

	app->Clear();

	double h = app->GetHeight()/2;
	double w = app->GetWidth()/2;

	for(vector<sf::String>::iterator it = items.begin(); it!= items.end(); ++it) {
	
		it->SetFont(sf::Font::GetDefaultFont());
		it->SetColor(sf::Color(0, 128, 128));
	   it->SetPosition(w, h);
	   it->SetSize(50.f);
	   app->Draw(*it);
	   
	   h+=it->GetRect().GetHeight();	 	  
	   
	}

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
	
	//app->Draw(sf::Shape::Rectangle(timg.GetX()-10,timg.GetY, sf::Color::Color(100,100,100)));

	
	app->Draw(test);	
	app->Draw(test2);
	app->Draw(test3);
	app->Draw(test4);
	app->Display();
	
//	int res;
//	scanf("%d",&res);

	while(app->IsOpened()) {
		sf::Event Event;
		while (app->GetEvent(Event)) {
			if (Event.Type == sf::Event::MouseButtonPressed) { 
				int i = 0;
				for(vector<sf::String>::iterator it = items.begin(); it!= items.end(); ++it) {
					if (it->GetRect().Contains(Event.MouseButton.X,Event.MouseButton.Y))
						return i;
					i++;
				}
			}				
		}
	}	
}

void Menu::aboutScene() {
	printf("About!\n");
}

void Menu::helpScene() {
	printf("Help!\n");
}
