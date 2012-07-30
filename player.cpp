/*
	player model class
	
	(c) roman filippov, 2012
*/
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "player.h"
#include "model.h"
#include "gameexception.h"

Player::Player(Model *model,const int &a,const int &b) : x(a), y(b), m(model) {

	rotation = 0;

	//if(m->checkRange(a,b)) {
//		x = a;
//		y = b;
//		m = model;
	//}
	//else
		//throw new GameException("wrong player position in constructor");
}

bool Player::moveTo(const int &a,const int &b) {
	
	rotation = ((a == x) ? acos(b-y) : asin(a-x))*360/(2*acos(-1))*(-1);
//	printf("rotation: %f\n",rotation);

	if (abs(a+b-x-y) == 1 && m->checkRange(a,b))
		if (m->getState(a,b) != GAME_WALL) {
			m->setState(x,y,GAME_EMPTY_CELL);
			x = a;
			y = b;
			m->setState(x,y,player_type);
			m->drawMap();
			return true;
		}
	else {
		m->drawMap();
		return false;
	}
}

void Player::setBoard(Model *b) {
	m = b;
}

void Player::setX(const int &newX) {
	if (m->checkRange(newX,y))
		x = newX;
}

void Player::setY(const int &newY) {
	if (m->checkRange(x,newY))
		y = newY;
}

