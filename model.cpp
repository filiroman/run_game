/*
	game model class
	
	(c) roman filippov, 2012
*/
#include <list>
#include <ctime>
#include <cstdlib>
#include <map>
#include <cstdio>
#include "model.h"
#include "gameexception.h"
#include "options.h"
#include "player.h"
#include "gamer.h"
#include "ai.h"
using std::list;
using std::pair;

Model::Model(Options *opt) {
//	if (fsize<5)												//ToDo: Check that in options
//		throw GameException("Wrong field size");
	b = NULL;
	board = NULL;
	options = opt;
}

bool Model::step() {
	for(list<Player>::iterator it=players.begin(); it!=players.end(); ++it)
		if(it->turn())		//Each player implements his own turn() method (ai or real gamer) return true if game is finished
			return true;
	return false;
}

void Model::createWalls() {
	srand( time (NULL) );	
	printf("Creating walls...");
	
	printf("Done\n");
}

void Model::createPlayers(int computers) {
	printf("Creating players...\n");

	Gamer g(this,0,0);				
	//addPlayer(g);									

	/*settings *st = options->getSettings();
	for (int i=0;i<computers;++i) {
		Ai a(const_cast<Model*>(this),st->size-1-i,st->size-1);
		addPlayer(a);
	}	*/	
					// + check path availability of every player
					
	printf("Done\n");
}

void Model::createWorld() {
	printf("Creating world...");

	settings *st = options->getSettings();
	int FIELD_SIZE = st->size;
	
	board = new char* [FIELD_SIZE];							//Creating array for 2 new
	b = new char [FIELD_SIZE*FIELD_SIZE];
	for(int i=0;i<FIELD_SIZE;++i)
		board[i] = &b[FIELD_SIZE*i];
		
	for(int i=0;i<FIELD_SIZE;i++)
		for(int j=0;j<FIELD_SIZE;j++)		
			board[i][j] = '0';
	printf("Done\n");
}

Model::~Model() {
	if (b != NULL)
		delete [] b;
	if (board != NULL)
		delete [] board;
}

bool Model::addPlayer(Player &p) {
	if (getState(p.getX(),p.getY()) == GAME_EMPTY_CELL) {
		board[p.getX()][p.getY()] = '1';
		p.setBoard(this);
		players.push_back(p);
		return true;
	}
	return false;
}
	

