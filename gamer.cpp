/*
	gamer (human player) model class
	
	(c) roman filippov, 2012
*/
#include "gamer.h"
#include "model.h"
#include "player.h"

virtual void Gamer::turn() {
	int a,b;
	scanf("%d%d",&a,&b);
	while (!moveTo(a,b)) {
		scanf("%d%d",&a,&b);
	}
	return;
}

Gamer::Gamer(Model *model,int &a=0,int &b=0) :Player(model,a,b) {};

