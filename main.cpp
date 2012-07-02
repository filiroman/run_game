/*
	main.cpp
	
	(c) roman filippov, 2012
*/
#include "application.h"

int main (int argc, char** argv) {
	
	Application *app = new Application();
	app->run();
	
	delete app;
	return EXIT_SUCCESS;
}

