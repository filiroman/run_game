/*
	computer enemy model class
	
	(c) roman filippov, 2012
*/
#include "ai.h"
#include "model.h"
#include "player.h"

virtual void Ai::turn() {
	int a,b;
	scanf("%d%d",&a,&b);
	while (!moveTo(a,b)) {
		scanf("%d%d",&a,&b);
	}
	return;
}

Ai::Ai(Model *model,int &a=0,int &b=0) :Player(model,a,b) {};
