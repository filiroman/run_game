/*
	game model class
	
	(c) roman filippov, 2012
*/
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "model.h"
#include "gamer.h"
#include "ai.h"

Model::Model(Options *opt) : board(NULL), options(opt) {
//	if (fsize<5)												//ToDo: Check that in options
//		throw GameException("Wrong field size");
}

bool Model::step() {
	for(list<PlayerPtr>::iterator it=players.begin(); it!=players.end(); ++it)
		if(it->get()->turn())						//Each player implements his own turn() method (ai or real gamer) 
			return false;								//return false if game is finished
	return true;
}

void Model::createWalls() {
	srand( time (NULL) );	
	printf("Creating walls...");
	
	printf("Done\n");
}

void Model::createPlayers(int computers) {
	printf("Creating players...");

	addPlayer(new Gamer(this,0,0));									
	//printf("%d %d\n",players.begin()->getX(),players.begin()->getY());

	settings *st = options->getSettings();
	//printf("%d\n",st->size);
	for (int i=0;i<computers;++i) {
		//Ai a(this,st->size-1-i,st->size-1);
		addPlayer(new Ai(this,st->size-1-i,st->size-1));
	}
					// + check path availability of every player
					
	printf("Done\n");
}

void Model::createWorld() {
	printf("Creating world...");

	settings *st = options->getSettings();
	int FIELD_SIZE = st->size;
	
	board = new char* [FIELD_SIZE];							//Creating map array
	for(int i=0;i<FIELD_SIZE;++i)
		board[i] = new char [FIELD_SIZE]();
		
	for(int i=0;i<FIELD_SIZE;i++)
		for(int j=0;j<FIELD_SIZE;j++)		
			board[i][j] = '0';
	printf("Done\n");
}

Model::~Model() {
	settings *st = options->getSettings();
	for(int i=0;i<st->size;++i)
		delete[] board[i];

	delete[] board;
}

bool Model::addPlayer(Player *p) {
	if (getState(p->getX(),p->getY()) == GAME_EMPTY_CELL) {
		board[p->getX()][p->getY()] = '1';
		p->setBoard(this);
		players.push_back(PlayerPtr(p));
		return true;
	}
	return false;
}
	

