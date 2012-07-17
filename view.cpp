/*
	view model class
	
	(c) roman filippov, 2012
*/
#include <cstdio>
#include "view.h"

int View::gameOverScene(const std::string &s) {
	printf("Game over! \n %s \n Retry? (1/0)",s.c_str());
	int m;
	scanf("%d",&m);
	return m ? GAME_ENDED_RETRY : GAME_ENDED_NO_RETRY;
}
