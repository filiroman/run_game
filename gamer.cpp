/*
	gamer (human player) model class
	
	(c) roman filippov, 2012
*/
#include "gamer.h"

virtual void Gamer::turn() {
	int a,b;
	scanf("%d%d",&a,&b);
	while (!moveTo(a,b)) {
		scanf("%d%d",&a,&b);
	}
	return;
}

