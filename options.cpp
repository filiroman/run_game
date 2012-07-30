/*
	options model class
	
	(c) roman filippov, 2012
*/
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include "options.h"
#include "application.h"
#include "view.h"

void Options::writeSettingsToStrings() {

	// cleaning items
	
	items_values.clear();

	// writing resolution to string
	char tmp[20];
	sf::VideoMode Mode = sf::VideoMode::GetMode(s->resolution);
	sprintf(tmp,"%dx%d",Mode.Width,Mode.Height);
	
	items_values.push_back(sf::String(tmp));
	
	// writing size to string
	
	switch (s->size) {
		case 10:
			items_values.push_back(sf::String("Small"));
			break;
		case 50:
			items_values.push_back(sf::String("Average"));
			break;
		case 100:
			items_values.push_back(sf::String("Large"));
			break;
		case 200:
			items_values.push_back(sf::String("Very Large"));
	}
	
	// writing walls count to string
	
	switch (s->walls) {
		case 0:
			items_values.push_back(sf::String("Low"));
			break;
		case 1:
			items_values.push_back(sf::String("Medium"));
			break;
		case 2:
			items_values.push_back(sf::String("High"));
	}
	
	// writing enemies count to string 
	
	sprintf(tmp,"%d",s->enemies);
	items_values.push_back(sf::String(tmp));
	
	// writing fullscreen
	
	items_values.push_back(sf::String(s->fullscreen ? "Yes" : "No"));
	
	// writing edges
	
	items_values.push_back(sf::String(s->edges ? "Yes" : "No"));
	
}

Options::Options(Application *apl) : AppLayer(apl), s(NULL) {
	if (!loadFromFile(OPTIONS_FILENAME))
		toDefaults();	
	items.push_back(sf::String("Options:"));
	items.push_back(sf::String("back to menu"));
	items.push_back(sf::String("To defaults"));
	items.push_back(sf::String("Resolution"));
	items.push_back(sf::String("Size"));
	items.push_back(sf::String("Walls"));
	items.push_back(sf::String("Enemies"));
	items.push_back(sf::String("Fullscreen"));
	items.push_back(sf::String("Edges"));
	
	writeSettingsToStrings();
}

void Options::toDefaults() {
	if (!loadFromFile(DEFAULT_FILENAME)) {
		
		if (s!=NULL) {
			delete s;
			s = NULL;
		}
		
		s = new Settings;
		s->resolution = 2;
		s->size = 10;
		s->walls = 1;
		s->enemies = 1;
		s->fullscreen = 0;
		s->edges = 1;
			
		save(DEFAULT_FILENAME);
	}
}

bool Options::loadFromFile(const string &filename) {
	FILE *f = fopen(filename.c_str(),"rb");
	if (f == NULL) return false;
	
	if (s!=NULL) {
		delete s;
		s = NULL;
	}
	
	s = new Settings;

	if (fread(s,sizeof(Settings),1,f) == 1) {
		fclose(f);
		return true;
	}
	fclose(f);
	return false;
}

void Options::save(const string &filename) const {
	FILE *f = fopen(filename.c_str(),"wb");
	assert(f != NULL);
	
	int n = fwrite(s,sizeof(Settings),1,f);
	assert(n == 1);
	fclose(f);
}

void Options::getSettingsToArray(int *&p) const {
	p = new int[sizeof(int)*OPT_SIZE]();
	p[0] = s->resolution;
	p[1] = s->size;
	p[2] = s->walls;
	p[3] = s->enemies;
	p[4] = static_cast<int>(s->fullscreen);
	p[5] = static_cast<int>(s->edges);	
}

void Options::optionsItemsDraw() {

	double w = 180, h = 60;

	View::getInstance(app)->menuDraw();
	writeSettingsToStrings();

	// Drawing "Options:" string

	items.begin()->SetFont(sf::Font::GetDefaultFont());
	items.begin()->SetColor(sf::Color(0, 128, 128));
	items.begin()->SetPosition(w, h);
	items.begin()->SetSize(50.f);
	app->Draw(*(items.begin()));	
	
	h+=items.begin()->GetRect().GetHeight()*2;
	
	//Drawing options and values strings
	
	int app_width = app->GetWidth();
	int i=0;
	for(vector<sf::String>::iterator it = items.begin()+3; it!= items.end(); ++it) {
	
		it->SetFont(sf::Font::GetDefaultFont());
		it->SetColor(sf::Color(0, 128, 128));
	   it->SetPosition(w, h);
	   it->SetSize(50.f);
	   app->Draw(*it);
	   
		items_values[i].SetFont(sf::Font::GetDefaultFont());
		items_values[i].SetColor(sf::Color(0, 128, 128));
	   items_values[i].SetSize(50.f);
	   items_values[i].SetPosition(app_width-items_values[i].GetRect().GetWidth()-20, h);
	   app->Draw(items_values[i]);
	   
	   h+=it->GetRect().GetHeight();	 	  
	   ++i;	   
	}
	
	// Drawing "Back to menu" string
	
	(items.begin()+1)->SetFont(sf::Font::GetDefaultFont());
	(items.begin()+1)->SetColor(sf::Color(0, 128, 128));
	(items.begin()+1)->SetPosition(w, h);
	(items.begin()+1)->SetSize(40.f);
	app->Draw(*(items.begin()+1));	
	
	// Drawing "To defaults" string
	
	(items.begin()+2)->SetFont(sf::Font::GetDefaultFont());
	(items.begin()+2)->SetColor(sf::Color(0, 128, 128));
	(items.begin()+2)->SetSize(40.f);
	(items.begin()+2)->SetPosition(app->GetWidth()-(items.begin()+2)->GetRect().GetWidth()-20, h);
	app->Draw(*(items.begin()+2));	
	
	app->Display();
}

void Options::changeOption(int num) {
	int *p;
	static int mapsize[] = {MAP_SMALL,MAP_AVERAGE,MAP_LARGE,MAP_HUGE};
	
	switch (num) {
		case 0:
			s->resolution = (s->resolution+1) % sf::VideoMode::GetModesCount();
			if (sf::VideoMode::GetMode(s->resolution).Width <MINIMUM_WIDTH)
				s->resolution = 0;
			break;
		case 1:
			p = std::find(mapsize,mapsize+4,s->size);
			if (p == mapsize+3)
				s->size = *(mapsize);
			else
				s->size = *(p+1);
				
			if (s->size < MIN_SIZE)
				s->size = MIN_SIZE;
			p = NULL;
			break;
		case 2:
			s->walls = (s->walls+1) % 3;
			break;
		case 3:
			s->enemies = (s->enemies+1) % (MAX_ENEMIES+1);
			if (s->enemies == 0)
				s->enemies = 1;
			break;
		case 4:
			s->fullscreen = !s->fullscreen;
			break;
		case 5:
			s->edges = !s->edges;
	}
}

void Options::optionsScene() {
	
	optionsItemsDraw();
	
	while(app->IsOpened()) {
		sf::Event Event;
		while (app->GetEvent(Event)) {
			if (Event.Type == sf::Event::MouseButtonPressed) { 
				int i = 0;
				for(vector<sf::String>::iterator it = items.begin()+3; it!= items.end(); ++it) {
					if (it->GetRect().Contains(Event.MouseButton.X,Event.MouseButton.Y) || items_values[i].GetRect().Contains(Event.MouseButton.X,Event.MouseButton.Y)) {
						changeOption(i);
						optionsItemsDraw();
					}
					
					else if ((items.begin()+1)->GetRect().Contains(Event.MouseButton.X,Event.MouseButton.Y)) {
						save();
						return;
					}			
					
					else if ((items.begin()+2)->GetRect().Contains(Event.MouseButton.X,Event.MouseButton.Y)) {
						toDefaults();
						return;
					}				
					++i;
				}
			}				
		}
	}	
}
	
Options::~Options() {
	save();
	delete s;
}
