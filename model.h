/*
	game model class
	
	(c) roman filippov, 2012
*/
#ifndef _MODEL_H_
#define _MODEL_H_
#include <list>
#include "player.h"
#include "gameexception.h"
using std::list;

class Model {
private:
	int FIELD_SIZE;
	char *b,**board;		//Game Board
	list<Player> Players;
	bool checkRange(int &x,int &y);
public:
	Model(int &fsize=10);
	~Model();
	bool addPlayer(Player &p);
	bool isEmpty(int &x,int &y);
	void setState(int &x,int &y,char &state);
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
