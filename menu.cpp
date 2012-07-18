/*
	menu model class
	
	(c) roman filippov, 2012
*/
//#include <string>
#include <SFML/Graphics.hpp>
#include <cstdio>
#include "application.h"
#include "menu.h"

Menu::Menu(Application *apl) {

	app = apl;

	items.push_back(sf::String("New Game"));
	items.push_back(sf::String("Settings"));
	items.push_back(sf::String("About"));
	items.push_back(sf::String("Help"));
	items.push_back(sf::String("Exit"));
}

int Menu::show() {

//    Hello.SetFont(sf::Font::GetDefaultFont());
//    Hello.SetColor(sf::Color(0, 128, 128));
//    Hello.SetPosition(100.f, 100.f);
//    Hello.SetRotation(15.f);
//    Hello.SetSize(50.f);
    
    double h = app->GetHeight()/2;
    double w = app->GetWidth()/2;

	for(vector<sf::String>::iterator it = items.begin(); it!= items.end(); ++it) {
	
//		printf("%s\n",it->c_str());
//	   Hello.SetText(it->c_str());
		it->SetFont(sf::Font::GetDefaultFont());
		it->SetColor(sf::Color(0, 128, 128));
	   it->SetPosition(w, h);
	   it->SetSize(50.f);
	   app->Draw(*it);
	   
	   h+=it->GetRect().GetHeight();	 	  
	   
	}
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
