/*
	computer enemy model class
	
	(c) roman filippov, 2012
*/
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "ai.h"
#include "model.h"
#include "player.h"
#include "options.h"
using std::set;
using std::pair;
using std::vector;

int near[] = {-1, 0, 1, 0, -1};

//bool mycompare::operator() (const int& lhs, const int& rhs) const {
//	return Ai::f(lhs)<Ai::f(rhs);
//};

//bool Ai::(*fn_pt)(int,int) = fncomp;

mycompare::mycompare (Ai *b) {
	a = b;
}

int Ai::h(const int &x) {
	return abs(x/n - target_x) + abs(x%n - target_y);
}

int Ai::f(const int &x) {
	return g[x/n][x%n] + h(x);
}

void Ai::A_star() {
	q.insert(x*n+y);
	g[x][y] = 0;
	p[x][y] = -1;
	while (!q.empty()) {
		set<int, bool(*)(int,int)>::iterator it = q.end(); it--;
		int v = *it;
		q.erase(it);
		int i = v/n, j = v%n;
		used[i][j] = true;
		if (i == target_x && j == target_y)
			return;
		
		for(int k=0;k<4;++k) {
			int h = i+near[k], l = j+near[k+1];
			if (h > n-1 || h < 0 || l > n-1 || l < 0)
				continue;
			if (used[h][l] || m->getState(h,l) == GAME_WALL)
				continue;
			
			bool better;
			set<int, Ai>::iterator ti = q.find(h*n+l);
			if (ti == q.end()) {
				p[h][l] = i*n+j;
				q.insert(h*n+l);	
			}
			else {
				g[i][j]+1 < g[h][l] ? better=true : better=false;
			}
			
			if (better) {
				p[h][l] = i*n+j;
				g[h][l] = g[i][j]+1;
			}					
		}
	}	
}

myvec Ai::path() {
	int k;
	k = p[target_x][target_y];
	myvec v;
	v.push_back(std::make_pair(target_x,target_y));
	while (k != -1) {
		v.push_back(std::make_pair(k/n,k%n));
		k = p[k/n][k%n];
		//printf("%d\n",k);
	}		
	std::reverse(v.begin(),v.end());		
	return v; 
}



void Ai::turn() {
	pair<int,int> a = m->getPlayerPosition();
	target_x = a.first;
	target_y = a.second;
	A_star();
	myvec b = path();
	moveTo(b[0].first,b[0].second);
}

Ai::Ai(Model *model,int &a,int &b) :Player(model,a,b) {
	//settings *st = model->options->getSettings();
//	fn_pt = (bool(*)(int,int))&Ai::fncomp;
	//q = q(fn_pt);
	
	n = (m->options->getSettings()).size;
	used = new bool* [n];
	for (int i=0;i<n;++i)
		used[i] = new bool[n];
	p = new int* [n];
	for (int i=0;i<n;++i)
		p[i] = new int[n];
	g = new int* [n];
	for (int i=0;i<n;++i)
		g[i] = new int[n];
	memset(used,0,sizeof(bool)*n*n);
	memset(p,0,sizeof(int)*n*n);
	memset(g,0,sizeof(int)*n*n);	
};


