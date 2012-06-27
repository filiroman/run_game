/*
	application model class
	
	(c) roman filippov, 2012
*/
#include <list>
#include "application.h"
#include "model.h"
using std::list;

Application::Application() {
	Model m;
	games.push_back(m);
}

void Application::newGame() {
	Model m;																		//in perspective to parallel games
	games.push_back(m);
}

void Application::run() {
	while (!games.empty()) 
		for (list<Model>::iterator it = games.begin(); it!= games.end(); ++it)
			if (it->step())
				it = games.erase(it);
}

/*Application::~Application() {
	for (list<Model*>::iterator it = games.begin(); it!= games.end(); ++it)
		delete it;
}*/
