/*
	application model class
	
	(c) roman filippov, 2012
*/
#ifndef _APPLICATION_H_
#define _APPLICATION_H_
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
//#include "model.h"
//#include "menu.h"
//#include "options.h"
class Model;
class Menu;
class Options;
class MapEditor;

using std::list;

class Application : public sf::RenderWindow {
private:
	Model *game;
	Menu *menu;
	Options *options;
	MapEditor *medit;
	double font_size; 				//just for fast access to font size from any class
	//list<Model> games;			//Using list in perspective to many parallel online games (each with menu and options)
public:
	Application();
	~Application();
	//void newGame();
	void run();	
	bool startGame();
	double getFontSize()const;
};

inline double Application::getFontSize() const {
	return font_size;
}

#endif
