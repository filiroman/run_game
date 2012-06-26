/*
	game model class
	
	(c) roman filippov, 2012
*/
#include <list>
#include "model.h"
#include "gameexception.h"
using std::list;


Model::Model(int &fsize=10) {
	if (fsize<5)
		throw GameException("Wrong field size");
	FIELD_SIZE = fsize;
	
	board = new int* [FIELD_SIZE];							//Creating array for 2 new
	b = new int [FIELD_SIZE*FIELD_SIZE];
	for(int i=0;i<FIELD_SIZE;++i)
		board[i] = &b[FIELD_SIZE*i];
		
	for(int i=0;i<FIELD_SIZE;i++)
		for(int j=0;j<FIELD_SIZE;j++)		
			board[i][j] = '0';
}

Model::~Model() {
	delete [] b;
	delete [] board;
}

bool Model::addPlayer(Player &p) {
	if (isEmpty(p->x(),p->y())){
		b[p->x()][p->y()] = '1';
		Players.push_back(p);
		p->setBoard(this);
		return true;
	}
	return false;
}
	

