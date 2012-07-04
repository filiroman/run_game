/*
	ai (computer player) model class
	
	(c) roman filippov, 2012
*/
#ifndef _AI_H_
#define _AI_H_
#include "player.h"
#include "model.h"

class Ai: public player {
public:
	Ai(Model *model,int &a=0,int &b=0);
	virtual void turn();
};

#endif
