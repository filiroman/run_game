/*
	computer enemy model class
	
	(c) roman filippov, 2012
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include "ai.h"
#include "model.h"
#include "player.h"
#include "options.h"


int near[] = {-1, 0, 1, 0, -1};

//bool mycompare::operator() (const int& lhs, const int& rhs) const {
//	return Ai::f(lhs)<Ai::f(rhs);
//};

//bool Ai::(*fn_pt)(int,int) = fncomp;

//mycompare::mycompare (Ai *b) {
//	a = b;
//}

int Ai::h(int x,int y) {
	//return abs(x/n - target_x) + abs(x%n - target_y);
	return abs(x - target_x) + abs(y - target_y);
}

int Ai::f(int x,int y) {
	//return g[x/n][x%n] + h(x);
	return g[x][y] + h(x,y);
}

void Ai::A_star() {
	printf("%d\n",used[0][0]);
	//pair<int,int> abc = std::make_pair(x*n+y,f(x,y));
	//printf("%d | %d \n",abc.first,abc.second);
	/*q.insert(std::make_pair(x*n+y,f(x,y)));
	g[x][y] = 0;
	p[x][y] = -1;
	while (!q.empty()) {
		set<pair<int,int>,mycompare>::iterator it = q.end(); it--;
		int v = (*it).first;
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
		 	it = q.find(std::make_pair(h*n+l,f(h,l)));
			if (it == q.end()) {
				p[h][l] = i*n+j;
				q.insert(std::make_pair(h*n+l,f(h,l)));
			}
			else {
				g[i][j]+1 < g[h][l] ? better=true : better=false;
			}
			
			if (better) {
				p[h][l] = i*n+j;
				g[h][l] = g[i][j]+1;
			}					
		}
	}	*/
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



bool Ai::turn() {
	pair<int,int> a = m->getPlayerPosition();
	target_x = a.first;
	target_y = a.second;
	A_star();
//	myvec b = path();
//	moveTo(b[0].first,b[0].second);
//	printf("Ai moves to: %d %d \n",b[0].first,b[0].second);
//	if (b[0].first == target_x && b[0].second == target_y) 
//		return true; 
//	else 
//		return false;
}

Ai::Ai(Model *model,int a,int b) :Player(model,a,b) {
	//settings *st = model->options->getSettings();
	//	fn_pt = (bool(*)(int,int))&Ai::fncomp;
	//q = q(fn_pt);
	
	settings *st = model->options->getSettings();
	n = st->size;
	
	used = new bool* [n];
	p = new int* [n];
	g = new int* [n];
	for (int i=0;i<n;++i) {
		used[i] = new bool[n];
		p[i] = new int[n];
		g[i] = new int[n];
	}		
	memset(used,0,sizeof(bool)*n*n);
	memset(p,0,sizeof(int)*n*n);
	memset(g,0,sizeof(int)*n*n);	
};

Ai::~Ai() {
	for (int i=0;i<n;++i) {
		delete[] g[i];
		delete[] p[i];
		delete[] used[i];
	}
	delete[] g;
	delete[] p;
	delete[] used;
}


