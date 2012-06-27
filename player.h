/*
	player model class
	
	(c) roman filippov, 2012
*/
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "model.h"

class Player {
private:
	int x,y;		//Position
	Model *m;
	// - Something else (maybe health, e.t.c)
public:
	Player(int &a=0,int &b=0);			//Initialize player on (x,y) position;
	bool MoveTo(int &a,int &b);
	void setBoard(Model &b);
	
	int x()const {			//inline
		return x;
	};
	int y()const {
		return y;
	};
		
	virtual void turn()=0;
};

inline void Player::setBoard(Model &b) {
	m = &b;
}

#endif
