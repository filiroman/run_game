/*
	menu model class
	
	(c) roman filippov, 2012
*/
//#include <string>
#include <SFML/Graphics.hpp>
#include <cstdio>
#include <string>
#include "application.h"
#include "menu.h"
#include "model.h"
#include "view.h"

using std::string;

Menu::Menu(Application *apl) : AppLayer(apl) {

	items.push_back(sf::String("New Game"));
	items.push_back(sf::String("Settings"));
	items.push_back(sf::String("Map Editor"));
	items.push_back(sf::String("About"));
	items.push_back(sf::String("Help"));
	items.push_back(sf::String("Exit"));
}

Menu::Menu(Application *apl, vector<string> menuItems) : AppLayer(apl) {
	for(vector<string>::iterator it = menuItems.begin(); it!= menuItems.end(); ++it) {
		items.push_back(sf::String(*it));
	}
}

int Menu::show() {

	app->Clear();
	View::getInstance(app)->menuDraw();

	double h = 180;//test.GetPosition().y+test.GetSubRect().GetHeight()*2;
	double w = 180;//test.GetPosition().x+test.GetSubRect().GetWidth()*2;

	for(vector<sf::String>::iterator it = items.begin(); it!= items.end(); ++it) {
	
		it->SetFont(sf::Font::GetDefaultFont());
		it->SetColor(sf::Color(0, 128, 128));
	   it->SetPosition(w, h);
	   it->SetSize(FONT_SIZE);
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
