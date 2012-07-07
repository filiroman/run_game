/*
	main.cpp
	
	(c) roman filippov, 2012
*/
#include <cstdio>
#include "application.h"
#include "gameexception.h"

int main (int argc, char** argv)try{
	
	Application *app = new Application();
	app->run();
	
	delete app;
	return EXIT_SUCCESS;
}
catch (GameException &e) {
	printf("%s",e.what());
}
catch (...) {
	printf("Unknown Error...\n");
}
