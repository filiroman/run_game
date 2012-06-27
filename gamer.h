/*
	gamer (human player) model class
	
	(c) roman filippov, 2012
*/
#ifndef _GAMER_H_
#define _GAMER_H_
#include "player.h"

class Gamer: public Player {
public:
	virtual void turn();
};

#endif
