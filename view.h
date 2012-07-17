/*
	view model class
	
	(c) roman filippov, 2012
*/
#ifndef _VIEW_H_
#define _VIEW_H_
#include <string>
/* gamestate enum (returns in player->turn)*/ 
#define GAME_ENDED_RETRY 0
#define GAME_RUNNING 1
#define GAME_ENDED_NO_RETRY 2

class View {
public:
	int gameOverScene(const std::string &s);	
};

#endif
