/*
	view model class
	
	(c) roman filippov, 2012
*/
#ifndef _VIEW_H_
#define _VIEW_H_
#include <string>
#include "applayer.h"
/* gamestate enum (returns in player->turn)*/ 
#define GAME_ENDED_RETRY 0
#define GAME_RUNNING 1
#define GAME_ENDED_NO_RETRY 2
#define GAME_NO_WAY 3

class Application;

class View : public AppLayer {
private:
	View(Application *apl);
	View(const View& v);
	const View& operator=(View&);
public:
	static const View* getInstance(Application *apl)	{
		static View single(apl);
		return &single;
	}
	int gameOverScene(const std::string &s)const;
	void menuDraw()const;	
};

#endif
