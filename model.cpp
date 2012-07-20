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
#include "view.h"
#include "application.h"
#include "gameexception.h"

Model::Model(Application *apl, Options *opt) : board(NULL), options(opt), app(apl) {
	view = new View(apl);
	
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
    
  	settings *st = options->getSettings();
	int FIELD_SIZE = st->size;
	
	unsigned int IMAGE_SIZE = gamerImg.GetWidth();
	
	app->Draw(sf::Shape::Rectangle(w, h, w+FIELD_SIZE*IMAGE_SIZE, h+FIELD_SIZE*IMAGE_SIZE, sf::Color::Color(100,100,100)));
	
	for (int i=0;i<FIELD_SIZE;++i) {
		for (int j=0;j<FIELD_SIZE;++j) {
			
			if (getState(i,j) == GAME_EMPTY_CELL)
				continue;
			if (getState(i,j) == GAME_WALL) {
				sf::Sprite tmp(boxImg);
				boxSpr.SetPosition(w+i*IMAGE_SIZE,h+j*IMAGE_SIZE);
				app->Draw(boxSpr);
			}
			else if (getState(i,j) == GAME_PLAYER) {
				sf::Sprite tmp(gamerImg);
				gamerSpr.SetPosition(w+j*IMAGE_SIZE,height-h-i*IMAGE_SIZE);
				app->Draw(gamerSpr);			
			}			
			else {
				sf::Sprite tmp(computerImg);
				computerSpr.SetPosition(w+j*IMAGE_SIZE,height-h-i*IMAGE_SIZE);
				app->Draw(computerSpr);
			}
		}
	}	
	app->Display();
}

void Model::createWalls() {
	srand( time (NULL) );	
	printf("Creating walls...");
	
	printf("Done\n");
}

void Model::createPlayers(int computers) {
	printf("Creating players...");
	
	players.reserve(computers+1);

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
			board[i][j] = GAME_EMPTY_CELL;
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
		board[p->getX()][p->getY()] = p->player_type;
		p->setBoard(this);
		players.push_back(PlayerPtr(p));
		return true;
	}
	return false;
}
	

