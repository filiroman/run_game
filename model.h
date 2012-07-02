/*
	main game model class
	
	(c) roman filippov, 2012
*/
#ifndef _MODEL_H_
#define _MODEL_H_
#include <list>
#include "player.h"
#include "gameexception.h"
#include "options.h"
#include "menu.h"
using std::list;

class Model {
private:
	Options *options;
	char *b,**board;		//Game Board
	list<Player> players;
	bool checkRange(int &x,int &y);
	void createWorld();
public:
	Model();
	~Model();
	bool addPlayer(Player &p);
	bool isEmpty(int &x,int &y);
	void setState(int &x,int &y,char &state);
	bool step();
};

inline bool Model::checkRange(int &x,int &y) {
	if (x<0 || y<0 || x>=FIELD_SIZE || y>=FIELD_SIZE)
		return false;
	return true;
}

inline bool Model::isEmpty(int &x,int &y) {
	if (checkRange(x,y))
		return board[x][y] == '0';
	else
		throw new GameException("wrong coordinates to check");
}

inline void Model::setState(int &x,int &y,char &state) {
	if (checkRange(x,y))
		board[x][y] = state;
	else
		throw new GameException("wrong coordinates to set state");
}

#endif
