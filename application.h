/*
	application model class
	
	(c) roman filippov, 2012
*/
#ifndef _AI_H_
#define _AI_H_
#include <list>
#include "model.h"
using std::list;

class Application {
private:
	//Model *Game;
	list<Model> games;			//Using list in perspective to many parallel online games (each with menu and options)
public:
	Application();
	void newGame();
	void run();
	//~Application();	
};

#endif
