/*
	main game model class
	
	(c) roman filippov, 2012
*/
#ifndef _MODEL_H_
#define _MODEL_H_
#include <list>
#include <map>
#include <boost/shared_ptr.hpp>
#include <SFML/Window.hpp>
#include "player.h"
#include "gameexception.h"
#include "options.h"
//#include "menu.h"
//#include "ai.h"
#define GAME_WALL 30
#define GAME_PLAYER 20
#define GAME_EMPTY_CELL 10
class Menu;
class Ai;
using std::list;
using std::pair;
typedef boost::shared_ptr<Player> PlayerPtr;

class Model: public sf::Window {
private:
	Options *options;
	char **board;		//Game Board
	list<PlayerPtr> players;
	void createWorld();
	void createWalls();
	void createPlayers(int computers=1);
public:
	Model(Options *opt);
	~Model();
	bool checkRange(int &x,int &y);
	bool addPlayer(Player *p);
	int getState(int x,int y);
	void setState(int &x,int &y,char state);
	bool step();
	pair<int,int> getPlayerPosition();
	friend class Ai;
	friend class Application;
};

inline pair<int,int> Model::getPlayerPosition() {
	return std::make_pair(players.begin()->get()->getX(),players.begin()->get()->getY());
}

inline bool Model::checkRange(int &x,int &y) {
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
