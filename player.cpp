/*
	player model class
	
	(c) roman filippov, 2012
*/
#include "player.h"
#include "model.h"
#include "gameexception.h"

Player::Player(Model *model,int &a,int &b) {
	if(m->checkRange(a,b)) {
		x = a;
		y = b;
		m = model;
	}
	else
		throw new GameException("wrong player position in constructor");
}

bool Player::moveTo(int &a,int &b) {
	if (abs(a+b-x+y) == 1 && m->getState(a,b) != GAME_WALL) {
		m->setState(x,y,'0');
		x = a;
		y = b;
		m->setState(x,y,'1');
		return true;
	}
	else
		return false;
}

void Player::setBoard(Model *b) {
	m = b;
}

