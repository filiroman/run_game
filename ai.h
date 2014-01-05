/*
	ai (computer player) model class
	
	(c) roman filippov, 2012
*/
#ifndef _AI_H_
#define _AI_H_
#include <set>
#include <map>
#include <vector>
#include <queue>
#include "player.h"

class Model;
using std::set;
using std::vector;
using std::pair;
using std::queue;

typedef vector<pair<int,int> > myvec;

class Ai: public Player {
private:	
	class mycompare {									//Compare class
	public:
		bool operator() (const pair<int,int>& lhs, const pair<int,int>& rhs) const {
			if (lhs.second == rhs.second)
				return lhs.first > rhs.first;
			return lhs.second > rhs.second;
		};
	};
	// fields
	int target_x, target_y, n;
	bool **used;
	int **p,**g;					//for A* (used, parents, g(x) )
	set<pair<int, int>, mycompare> q;
	queue<int> qt;
	// methods
	void A_star();
	myvec path() const;
	void clear();
	int h(const int &x,const int &y) const;
	int f(const int &x,const int &y) const;
public:
	Ai(Model *model,const int &a,const int &b);
	void BFS_PathFinding(const int &cx,const int &cy);
	int test_turn();
	virtual int turn();
	virtual ~Ai();
};

#endif
