/*
	ai (computer player) model class
	
	(c) roman filippov, 2012
*/
#ifndef _AI_H_
#define _AI_H_
#include <set>
#include <map>
#include "player.h"
#include "model.h"
using std::set;

typedef vector<std::pair<int,int> > myvec;

class Ai: public Player {
private:

	//class mycompare {									//Compare class
	//public:
	bool operator() (const int& lhs, const int& rhs) const {
		return f(lhs)<f(rhs);
	};
	//};
	int target_x, target_y, n;
	bool **used;
	int **p,**g;					//for A* (used, parents, g(x) )
	set<int, Ai> q;
	int h(const int &x);
	int f(const int &x)const;
	void A_star();
	myvec path();
public:
	Ai(Model *model,int &a,int &b);
	virtual void turn();
};

#endif
