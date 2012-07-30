/*
	computer enemy model class
	
	(c) roman filippov, 2012
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <SFML/System.hpp>
#include "ai.h"
#include "model.h"
#include "player.h"
#include "options.h"
#include "view.h"
#include "application.h"

const int INF = 1000*1000;

int near[] = {-1, 0, 1, 0, -1};

int Ai::h(const int &x,const int &y) const {
	return abs(x - target_x) + abs(y - target_y);
}

int Ai::f(const int &x,const int &y) const {
	return g[x][y] + h(x,y);
}

void Ai::clear() {
	for (int i=0;i<n;++i) {
		memset(used[i],0,sizeof(bool)*n);
				
		for (int j=0;j<n;++j) {
			p[i][j] = INF;
			g[i][j] = INF;
		}
	}
	q.clear();
}

void Ai::A_star() {											//A star realisation for Ai turn
	clear();			//cleaning arrays and set before every turn
	q.insert(std::make_pair(x*n+y,f(x,y)));	//pushing current ai pos to set (pos,f(x,y))
	g[x][y] = 0;
	p[x][y] = -1;
	while (!q.empty()) {	
		set<pair<int,int>,mycompare>::iterator it = q.end(); it--;		//set sort all pairs of (f1>f2), so in q.end()-- 
		int v = it->first;															//would be elem with minimum f
																					//see ai.h mycompare class for more		
		q.erase(it);
		int i = v/n, j = v%n;
		used[i][j] = true;

		if (i == target_x && j == target_y)
			return;
		
		for(int k=0;k<4;++k) {
			int h = i+near[k], l = j+near[k+1];
			if (h > n-1 || h < 0 || l > n-1 || l < 0)
				continue;
			if (used[h][l] || m->getState(h,l) == GAME_WALL || m->getState(h,l) == GAME_ENEMY)
				continue;
			
			bool better = false;
		 	it = q.find(std::make_pair(h*n+l,f(h,l)));
		 	
			if (it == q.end()) {
				p[h][l] = i*n+j;
				g[h][l] = g[i][j]+1;
				q.insert(std::make_pair(h*n+l,f(h,l)));
			}
			else {
				better = g[i][j]+1 < g[h][l];
			}
			
			if (better) {
				q.erase(it);
				p[h][l] = i*n+j;
				g[h][l] = g[i][j]+1;
				q.insert(std::make_pair(h*n+l,f(h,l)));
			}					
		}
	}	
}


/* realisation ai pathfinding through Breadth-first search [ I think it's faster [O(V+E)] than A* (like Djikstra), but when we have egdes with different weight we must use A* or Dijkstra ] */

void Ai::BFS_PathFinding(const int &cx,const int &cy) {
	
	clear();
	qt = queue<int> ();
		
	qt.push(cx*n+cy);
	p[cx][cy] = -1;
	
	while (!qt.empty()) {
		
		int v = qt.front();
		qt.pop();
		
		int i = v/n, j = v%n;
		used[i][j] = true;
		
		if (i == target_x && j == target_y)
			return;
		for(int k=0;k<4;++k) {
			int h = i+near[k], l = j+near[k+1];
//			if (h > n-1 || h < 0 || l > n-1 || l < 0)
//				continue;
			if (!m->checkRange(h,l))
				continue;
			if (used[h][l] || m->getState(h,l) == GAME_WALL || m->getState(h,l) == GAME_ENEMY)
				continue;
				
			p[h][l] = i*n+j;
			qt.push(h*n+l);
		}
	}
}

myvec Ai::path() const {							//restore path from parents array
	int k;
	k = p[target_x][target_y];
	myvec v;
	
//	printf("%d | %d | k = %d\n",target_x,target_y,k);
	
	if (k == INF) {
		return v;
	}
		
	v.push_back(std::make_pair(target_x,target_y));
	while (k != -1) {
		v.push_back(std::make_pair(k/n,k%n));
		k = p[k/n][k%n];
	}		
	
	//m->players.begin()->get()->turn();
	
	std::reverse(v.begin(),v.end());		
	return v; 
}


/* function finds the shortest path to gamer and moves computer on it */

int Ai::turn() {

	//real player move (just for easier game and multithreading emulation)
	int r;
	for (int i=0;i<30;++i) {
		usleep(1000*30);
		if((r = m->players.begin()->get()->turn()) != GAME_RUNNING)
			return r;
	}
	pair<int,int> a = m->getPlayerPosition();
	target_x = a.first;
	target_y = a.second;
		
	A_star();	
//	BFS_PathFinding(x,y);
	myvec b = path();	
	
	if (b.empty())
	return GAME_NO_WAY;
	
//	for(myvec::iterator it = b.begin();it!= b.end();++it)
//		printf("%d | %d\n",it->first,it->second);
								
	moveTo(b[1].first,b[1].second);			//moving
	
	char log_str[30];
	sprintf(log_str,"Ai moves to: %d %d",b[1].first,b[1].second);
	m->addLogString(sf::String(log_str));
	
	if (b[1].first == target_x && b[1].second == target_y) 
		return m->view->gameOverScene("You Lose!");
	else 
		return GAME_RUNNING;
}


/* turn function for testing path availability for every computer player before the game starts, don't perform move, just checks */

int Ai::test_turn() {

	pair<int,int> a = m->getPlayerPosition();
	target_x = a.first;
	target_y = a.second;
		
	A_star();
//	printf("Finding path!\n");
//	BFS_PathFinding(x,y);
	myvec b = path();		
	
	if (b.empty())
		return GAME_NO_WAY;
	else return GAME_RUNNING;
}

/* Ai constructor */

Ai::Ai(Model *model,const int &a,const int &b) :Player(model,a,b) {

	player_type = GAME_ENEMY;	// Might be a GAME_PLAYER for real player
	rotation = -180;
		
	n = model->MAP_SIZE;			// getting the size of map;
	
	used = new bool* [n];
	p = new int* [n];
	g = new int* [n];
	for (int i=0;i<n;++i) {
		used[i] = new bool[n]();
		p[i] = new int[n]();
		g[i] = new int[n]();
	}			
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
	printf("Ai Deleted!\n");
}


