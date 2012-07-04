/*
	player model class
	
	(c) roman filippov, 2012
*/
#include "player.h"
#include "model.h"
#include "gameexception.h"

Player::Player(Model *model,int &a=0,int &b=0) {
	if(m->checkRange(a,b)) {
		x = a;
		y = b;
		m = model;
	}
	else
		throw new GameException("wrong player position in constructor");
}

bool Player::moveTo(int &a,int &b) {
	if (abs(a+b-x+y) == 1 && m->isEmpty(a,b)) {
		m->setState(x,y,'0');
		x = a;
		y = b;
		m->setState(x,y,'1');
		return true;
	}
	else
		return false;
}
