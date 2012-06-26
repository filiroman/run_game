/*
	gamer (human player) model class
	
	(c) roman filippov, 2012
*/
#ifndef _GAMER_H_
#define _GAMER_H_
#include "player.h"

class Gamer: public Player {
	virtual void turn();
};

virtual void Gamer::turn() {
	int a,b;
	scanf("%d%d",&a,&b);
	while (!moveTo(a,b)) {
		scanf("%d%d",&a,&b);
	}
	return;
}

#endif
