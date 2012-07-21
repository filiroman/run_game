/*
	options model class
	
	(c) roman filippov, 2012
*/
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include "options.h"
#include "application.h"

Options::Options(Application *apl) {
	app = apl;
	if (!loadFromFile(OPTIONS_FILENAME))
		toDefaults();	
}

void Options::toDefaults() {
	if (!loadFromFile(DEFAULT_FILENAME)) {
		
		s = new settings;
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
	s = new settings;
	
	if (fread(s,sizeof(settings),1,f) == 1) {
		fclose(f);
		return true;
	}
	fclose(f);
	return false;
}

void Options::save(const string &filename) {
	FILE *f = fopen(filename.c_str(),"wb");
	assert(f != NULL);
	
	int n = fwrite(s,sizeof(settings),1,f);
	assert(n == 1);
	fclose(f);
}

settings *Options::getSettings() {
	return s;
}

void Options::optionsScene() {

	sf::String Opt("Retry?");
	Opt.SetFont(sf::Font::GetDefaultFont());
	Opt.SetColor(sf::Color(0, 128, 128));
	Opt.SetPosition(app->GetWidth()/2, app->GetHeight()/2);
	Opt.SetSize(50.f);
	
	sf::String Yes("Yes/"), No("No");
	Yes.SetFont(sf::Font::GetDefaultFont());
	Yes.SetColor(sf::Color(0, 128, 128));
//	Yes.SetPosition(GameOver.GetPosition().x, GameOver.GetPosition().y + GameOver.GetRect().GetHeight());
	Yes.SetSize(50.f);
	
	No.SetFont(sf::Font::GetDefaultFont());
	No.SetColor(sf::Color(0, 128, 128));
//	No.SetPosition(GameOver.GetPosition().x + Yes.GetRect().GetWidth(), GameOver.GetPosition().y + GameOver.GetRect().GetHeight());
	No.SetSize(50.f);
	
	app->Draw(Opt);
	app->Draw(Yes);
	app->Draw(No);
	app->Display();
}
	
Options::~Options() {
	save();
}
