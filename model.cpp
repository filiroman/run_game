/*
	game model class
	
	(c) roman filippov, 2012
*/
#include <list>
#include "model.h"
#include "gameexception.h"
#include "options.h"
using std::list;


Model::Model() {
	if (fsize<5)
		throw GameException("Wrong field size");
	options = new Options();	
	menu = new Menu();	
	b = NULL;
	board = NULL;
}

bool Model::step() {
	for(list<Player>::iterator it=players.begin(); it!=players.end(); ++it)
		if(it->turn())
			return true;
	return false;
}

void Model::createWorld() {

	settings *st = options->getSettings();
	int FIELD_SIZE = st->size;
	
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
	delete menu;
	delete options;
}

bool Model::addPlayer(Player &p) {
	if (isEmpty(p.x(),p.y())){
		b[p.x()][p.y()] = '1';
		p.setBoard(this);
		players.push_back(p);
		return true;
	}
	return false;
}
	

