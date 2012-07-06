/*
	ai (computer player) model class
	
	(c) roman filippov, 2012
*/
#ifndef _AI_H_
#define _AI_H_
#include <set>
#include <map>
#include <vector>
#include "player.h"
//#include "model.h"
class Model;
using std::set;
using std::vector;
using std::pair;

typedef vector<pair<int,int> > myvec;

class mycompare {									//Compare class
private:
	Ai *a;
public:
	mycompare(Ai *b);
	bool operator() (const int& lhs, const int& rhs) const {
		return (a->f(lhs))<(a->f(rhs));
	};
};

//bool fncomp (int lhs, int rhs,Ai *a) { return (a->f(lhs))<(a->f(rhs)); };
//bool(*fn_pt)(int,int,Ai) = fncomp


class Ai: public Player {
private:	
	int target_x, target_y, n;
	bool **used;
	int **p,**g;					//for A* (used, parents, g(x) )
	set<int, mycompare(this)> q;
	int h(const int &x);
	int f(const int &x);
	void A_star();
	myvec path();
public:
	Ai(Model *model,int &a,int &b);
	virtual void turn();
};

#endif
