/*
	game model class
	
	(c) roman filippov, 2012
*/
#include <list>
#include <ctime>
#include <cstdlib>
#include <map>
#include "model.h"
#include "gameexception.h"
#include "options.h"
#include "player.h"
#include "gamer.h"
#include "ai.h"
using std::list;
using std::pair;

Model::Model(Options *opt) {
	if (fsize<5)
		throw GameException("Wrong field size");
	b = NULL;
	board = NULL;
	options = opt;
}

pair<int,int> Model::getPlayerPosition() {
	return std::make_pair(players.begin()->getX(),players.begin()->getY());
}

bool Model::step() {
	for(list<Player>::iterator it=players.begin(); it!=players.end(); ++it)
		if(it->turn())		//Each player implements his own turn() method (ai or real gamer) return true if game is finished
			return true;
	return false;
}

void Model::createWalls() {
	srand( time (NULL) );	
	printf("Creating walls...\n");


}

void Model::createPlayers(int computers=1) {
	printf("Creating players...\n");

	Gamer g(this,0,0);				
	addPlayer(g);									

	settings *st = options->getSettings();
	for (int i=0;i<computers;++i) {
		Ai a(this,st.size-1-i,st.size-1);
		addPlayer(a);
	}		
					// + check path availability of every player
}

void Model::createWorld() {
	printf("Creating world...\n");

	settings *st = options->getSettings();
	int FIELD_SIZE = st.size;
	
	board = new int* [FIELD_SIZE];							//Creating array for 2 new
	b = new int [FIELD_SIZE*FIELD_SIZE];
	for(int i=0;i<FIELD_SIZE;++i)
		board[i] = &b[FIELD_SIZE*i];
		
	for(int i=0;i<FIELD_SIZE;i++)
		for(int j=0;j<FIELD_SIZE;j++)		
			board[i][j] = '0';
}

Model::~Model() {
	if (b != NULL)
		delete [] b;
	if (board != NULL)
		delete [] board;
}

bool Model::addPlayer(Player &p) {
	if (getState(p.getX(),p.getY()) == GAME_EMPTY_CELL) {
		b[p.getX()][p.getY()] = '1';
		p.setBoard(this);
		players.push_back(p);
		return true;
	}
	return false;
}
	

