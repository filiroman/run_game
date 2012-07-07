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

//bool fncomp (int lhs, int rhs,Ai *a) { return (a->f(lhs))<(a->f(rhs)); };
//bool(*fn_pt)(int,int,Ai) = fncomp


class Ai: public Player {
private:	
	class mycompare {									//Compare class
	public:
		bool operator() (const pair<int,int>& lhs, const pair<int,int>& rhs) const {
			return lhs.second<rhs.second;
		};
	};
	int target_x, target_y, n;
	bool **used;
	int **p,**g;					//for A* (used, parents, g(x) )
	set<pair<int,int>,mycompare> q;
	int h(int &x,int &y);
	int f(int &x,int &y);
	void A_star();
	myvec path();
public:
	Ai(Model *model,int a,int b);
	virtual bool turn();
};

#endif
