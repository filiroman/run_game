/*
	game model class
	
	(c) roman filippov, 2012
*/
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "model.h"
#include "gamer.h"
#include "ai.h"
#include "view.h"
#include "application.h"
#include "gameexception.h"

Model::Model(Application *apl, Options *opt) : AppLayer(apl), board(NULL), options(opt) {
	view = View::getInstance(apl);
	
	FIELD_SIZE = options->getSettings()->size;
	
   if (!gamerImg.LoadFromFile(GAME_RESOURCES(player_game.png)))
   	throw new GameException("no file to load: player_game.png");
 	gamerSpr = sf::Sprite(gamerImg);   	
   
   if (!boxImg.LoadFromFile(GAME_RESOURCES(box_game.png)))
   	throw new GameException("no file to load: box_game.png");
	boxSpr = sf::Sprite(boxImg);   	
   
   if (!cellImg.LoadFromFile(GAME_RESOURCES(cell_game.png)))
   	throw new GameException("no file to load: cell_game.png");
   cellSpr = sf::Sprite(cellImg); 
   
   if (!computerImg.LoadFromFile(GAME_RESOURCES(computer_game.png)))
   	throw new GameException("no file to load: computer_game.png");
   computerSpr = sf::Sprite(computerImg);
}

int Model::step() {

	drawMap();
	int res;
	while (1) {
		for(vector<PlayerPtr>::iterator it=players.begin()+1; it!=players.end(); ++it) {
			//usleep(1000*300);
			if((res = players.begin()->get()->turn()) != GAME_RUNNING) 
				return res;
			
			if((res = it->get()->turn()) != GAME_RUNNING)	 //Each player implements his own turn() method (ai or real)
				if (res != GAME_NO_WAY)
					return res;								
				
			drawMap();
			app->Display();
		}
	}
}

void Model::drawMap() {
	
	app->Clear();
	
	unsigned int height = app->GetHeight();
   double h = height/8;
   double w = app->GetWidth()/6;
	
	unsigned int IMAGE_SIZE = gamerImg.GetWidth();
	
	app->Draw(sf::Shape::Rectangle(w, h, w+FIELD_SIZE*IMAGE_SIZE, h+FIELD_SIZE*IMAGE_SIZE, sf::Color::Color(100,100,100)));
	
	for (int i=0;i<FIELD_SIZE;++i) {
		for (int j=0;j<FIELD_SIZE;++j) {
			
			if (getState(i,j) == GAME_EMPTY_CELL)
				continue;
			if (getState(i,j) == GAME_WALL) {
//				boxSpr.SetPosition(w+j*IMAGE_SIZE,height-h-i*IMAGE_SIZE);
				boxSpr.SetPosition(w+j*IMAGE_SIZE,h+i*IMAGE_SIZE);
				app->Draw(boxSpr);
			}
			else if (getState(i,j) == GAME_PLAYER) {
			
				double rot = players.begin()->get()->rotation;
				int si=i,sj=j;
				if (rot > 0 || rot <-90)
					++si;
				if (rot < 0)
					++sj;
				gamerSpr.SetRotation(rot);
				gamerSpr.SetPosition(w+sj*IMAGE_SIZE,h+si*IMAGE_SIZE);

				app->Draw(gamerSpr);			
			}			
			else if (getState(i,j) == GAME_ENEMY) {
				for(vector<PlayerPtr>::iterator it = players.begin()+1; it!=players.end(); ++it) {
					if (it->get()->getX() == i && it->get()->getY() == j) {
						double rot = it->get()->rotation;
						int si=i,sj=j;
						if (rot > 0 || rot <-90)
							++si;
						if (rot < 0)
							++sj;
						computerSpr.SetRotation(rot);
						computerSpr.SetPosition(w+sj*IMAGE_SIZE,h+si*IMAGE_SIZE);
						break;
					}
				}
				app->Draw(computerSpr);
			}
		}
	}	
	app->Display();
}

bool Model::checkPaths() {
	for(vector<PlayerPtr>::iterator it=players.begin()+1; it!=players.end(); ++it) {
		if (static_cast<Ai*>(it->get())->test_turn() == GAME_NO_WAY)
			return false;
	}
	return true;
}

void Model::createWalls() {
	srand( time (NULL) );	
	printf("Creating walls...");
	
	for(int i=0;i<FIELD_SIZE;i++)
		for(int j=0;j<FIELD_SIZE;j++)		
			board[i][j] = (rand()%4 == 1) ? GAME_WALL : GAME_EMPTY_CELL;
	
	printf("Done\n");
}

void Model::createPlayers(int computers) {
	printf("Creating players...");
	
	players.clear();
	players.reserve(computers+1);

	addPlayer(new Gamer(this,0,0));									

	for (int i=0;i<computers;++i) {
		addPlayer(new Ai(this,FIELD_SIZE-1-i,FIELD_SIZE-1));
	}
					
	printf("Done\n");
}

void Model::createWorld() {
	printf("Creating world...");
	
	board = new char* [FIELD_SIZE];							//Creating map array
	for(int i=0;i<FIELD_SIZE;++i)
		board[i] = new char [FIELD_SIZE]();
		
//	for(int i=0;i<FIELD_SIZE;i++)
//		for(int j=0;j<FIELD_SIZE;j++)		
//			board[i][j] = GAME_EMPTY_CELL;
	printf("Done\n");
}

Model::~Model() {

	for(int i=0;i<FIELD_SIZE;++i)
		delete[] board[i];

	delete[] board;
	
	view = NULL;
	options = NULL;
}

bool Model::addPlayer(Player *p) {
	int x = p->getX(),
		 y = p->getY(),
		 ptype = p->player_type;
		 
//	if (getState(x,y) == GAME_EMPTY_CELL) {

	setState(x, y, ptype);
	p->setBoard(this);
	players.push_back(PlayerPtr(p));
	return true;
	
//	}
//	return false;
}
	

