/*
	gamer (human player) model class
	
	(c) roman filippov, 2012
*/
#ifndef _GAMER_H_
#define _GAMER_H_
#include "player.h"
//#include "model.h"
class Model;

class Gamer: public Player {
public:
	Gamer(Model *model,const int &a,const int &b);
	virtual int turn();
};

#endif
