/*
	main game model class
	
	(c) roman filippov, 2012
*/
#ifndef _MODEL_H_
#define _MODEL_H_
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <string>
#include "player.h"
#include "view.h"
#include "gameexception.h"
#include "options.h"

/* map cells state defines (returned by model->getState)*/
#define GAME_WALL 30
#define GAME_PLAYER 20
#define GAME_EMPTY_CELL 10

/* defines Game window header */
#define GAME_WINDOW_NAME "Run Game"

/* predeclarations of Model used classes */
class Menu;
class Ai;
//class View;
class Application;

using std::vector;
using std::pair;
using std::string;

/* Smart pointers from boost library, used to keep pointers to Players in container */
typedef boost::shared_ptr<Player> PlayerPtr;

class Model {
private:
	Options *options;
	char **board;		//Game Board
	View *view;
	Application *app;
	vector<PlayerPtr> players;
	void createWorld();
	void createWalls();
	void createPlayers(int computers=1);
public:
	Model(Application *apl, Options *opt);
	~Model();
	bool checkRange(const int &x,const int &y);
	bool addPlayer(Player *p);
	int getState(int x,int y);
	void setState(int &x,int &y,char state);
	int step();
	void drawMap();
	pair<int,int> getPlayerPosition();
	friend class Gamer;
	friend class Ai;
	friend class Application;
};

inline pair<int,int> Model::getPlayerPosition() {
	return std::make_pair(players.begin()->get()->getX(),players.begin()->get()->getY());
}

inline bool Model::checkRange(const int &x,const int &y) {
	settings *st = options->getSettings();
	int FIELD_SIZE = st->size;
	if (x<0 || y<0 || x>=FIELD_SIZE || y>=FIELD_SIZE)
		return false;
	return true;
}

inline int Model::getState(int x,int y) {
	if (checkRange(x,y)) {
		if (board[x][y] == '0')
			return GAME_EMPTY_CELL;
		else if (board[x][y] == '2')
			return GAME_WALL;
		else 
			return GAME_PLAYER;
	}
	else
		throw new GameException("wrong coordinates to check");
}

inline void Model::setState(int &x,int &y,char state) {
	if (checkRange(x,y))
		board[x][y] = state;
	else
		throw new GameException("wrong coordinates to set state");
}

#endif
