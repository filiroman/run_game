/*
	gamer (human player) model class
	
	(c) roman filippov, 2012
*/
#include <cstdio>
#include "gamer.h"
#include "model.h"
#include "player.h"

bool Gamer::turn() {
	int a,b;
	scanf("%d%d",&a,&b);
	while (!moveTo(a,b)) {
		scanf("%d%d",&a,&b);
	}
	printf("%d %d \n",a,b);
	return false; 		//temporarily
}

Gamer::Gamer(Model *model,int a,int b) :Player(model,a,b) {};

