/*
	game model class
	
	(c) roman filippov, 2012
*/
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include "model.h"
#include "gamer.h"
#include "ai.h"
#include "view.h"
#include "application.h"

Model::Model(Application *apl, Options *opt) : AppLayer(apl), board(NULL), options(opt) {
	view = View::getInstance(apl);
	
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
   
   if (!miniMapImg.LoadFromFile(GAME_RESOURCES(map_cell_small.png)))
   	throw new GameException("no file to load: map_cell_small.png");
   miniMapSpr = sf::Sprite(miniMapImg);
   
   if (!miniMapPlayerImg.LoadFromFile(GAME_RESOURCES(map_cell_player_small.png)))
   	throw new GameException("no file to load: map_cell_player_small.png");
   miniMapPlayerSpr = sf::Sprite(miniMapPlayerImg);
   
  	MAP_SIZE = options->getSettings()->size;
  	FIELD_SIZE = MAP_SIZE;
  	unsigned int IMAGE_SIZE = gamerImg.GetWidth();
  	
  	int msize = FIELD_SIZE*IMAGE_SIZE - app->GetHeight() + IMAGE_SIZE*2;
  	
  	printf("MAP_SIZE=%d\n",MAP_SIZE);
  	
  	if (msize > 0)
  		FIELD_SIZE -= ceil((msize+0.0f)/IMAGE_SIZE);
  	
	int cells_count = MAP_SIZE/FIELD_SIZE + static_cast<bool> (MAP_SIZE%FIELD_SIZE);
  	
  	msize = FIELD_SIZE*IMAGE_SIZE + cells_count*miniMapImg.GetWidth()  - app->GetWidth();
  	if (msize > 0)
		FIELD_SIZE -= ceil((msize+0.0f)/IMAGE_SIZE);
 	printf("FIELD_SIZE=%d\n",FIELD_SIZE);  	
}

int Model::step() {

	drawMap();
	int res;
	while (1) {
		for(vector<PlayerPtr>::iterator it=players.begin()+1; it!=players.end(); ++it) {
			if((res = players.begin()->get()->turn()) != GAME_RUNNING) 
				return res;
			
			if((res = it->get()->turn()) != GAME_RUNNING)	 //Each player implements his own turn() method (ai or real)
				if (res != GAME_NO_WAY)
					return res;								
				
			drawMap();
		}
	}
}

void Model::drawLogStrings(const int &x, const int &y) {
	int h = y;
	for(vector<sf::String>::iterator it = log_strings.begin(); it!= log_strings.end(); ++it) {
	
		it->SetFont(sf::Font::GetDefaultFont());
		it->SetColor(sf::Color(200, 200, 149));
	   it->SetPosition(x, h);
	   it->SetSize(FONT_SIZE/3);
	   app->Draw(*it);
	   
	   h+=it->GetRect().GetHeight();	 
	}
}

void Model::drawMiniMap() {

	unsigned int IMAGE_SIZE = gamerImg.GetWidth();
	double h = 50; 				//app->GetHeight()/2-FIELD_SIZE*IMAGE_SIZE/2;
   double w = 50;					//app->GetWidth()/2-FIELD_SIZE*IMAGE_SIZE/3*2;
	
	pair<int,int> pos = getPlayerPosition();
	int i_now = pos.first/FIELD_SIZE*FIELD_SIZE;
	int j_now = pos.second/FIELD_SIZE*FIELD_SIZE;
	int max_value_j = j_now+FIELD_SIZE;
		
	int cells_count = MAP_SIZE/FIELD_SIZE + static_cast<bool> (MAP_SIZE%FIELD_SIZE);
		
	int mini_map_w = w+(max_value_j-j_now)*IMAGE_SIZE+10,
		 mini_map_h = h-2;
		 
	int mutable_w = mini_map_w,
		 mutable_h = mini_map_h;
		 
	if (cells_count>1) {	 
	
		sf::String miniText("Mini Map:",sf::Font::GetDefaultFont(),FONT_SIZE/2);
		miniText.SetPosition(mini_map_w,mini_map_h-miniText.GetRect().GetHeight());
		app->Draw(miniText);
			 
		for (int i=0;i<cells_count;++i) {
			mutable_w = mini_map_w;
			for (int j=0;j<cells_count;++j) {
			
				if (i_now/FIELD_SIZE == i && j_now/FIELD_SIZE == j) {
					miniMapPlayerSpr.SetPosition(mutable_w,mutable_h);
					app->Draw(miniMapPlayerSpr);	
				}
				else {
					miniMapSpr.SetPosition(mutable_w,mutable_h);
					app->Draw(miniMapSpr);	
				}
				mutable_w += miniMapImg.GetWidth();				
			}		
			mutable_h += miniMapImg.GetHeight();
		}
		
		sf::String finishText("<-Finish!",sf::Font::GetDefaultFont(),FONT_SIZE/3);
		finishText.SetPosition(mutable_w+4,mutable_h-miniMapImg.GetHeight());
		app->Draw(finishText);
	}
	drawLogStrings(mini_map_w,mutable_h);
}

void Model::drawMap() {
	
	app->Clear(sf::Color::Color(100,100,100));
	
	unsigned int height = app->GetHeight();
	unsigned int IMAGE_SIZE = gamerImg.GetWidth();
	
   double h = 50;					//height/2-FIELD_SIZE*IMAGE_SIZE/2;
   double w = 50;					//app->GetWidth()/2-FIELD_SIZE*IMAGE_SIZE/3*2;
	
	pair<int,int> pos = getPlayerPosition();
	int i_now = pos.first/FIELD_SIZE*FIELD_SIZE;
	int j_now = pos.second/FIELD_SIZE*FIELD_SIZE;
	int max_value_i = i_now+FIELD_SIZE;
	int max_value_j = j_now+FIELD_SIZE;
	
	if (max_value_i > MAP_SIZE)
		max_value_i = MAP_SIZE;
	if (max_value_j > MAP_SIZE)
		max_value_j = MAP_SIZE;
	
	app->Draw(sf::Shape::Rectangle(w-2, h-2, w+(max_value_j-j_now)*IMAGE_SIZE+2, h+(max_value_i-i_now)*IMAGE_SIZE+2, sf::Color::Color(200,200,149)));
	
	app->Draw(sf::Shape::Rectangle(w, h, w+(max_value_j-j_now)*IMAGE_SIZE, h+(max_value_i-i_now)*IMAGE_SIZE, sf::Color::Color(50,50,50)));
	
	drawMiniMap();										//Draws mini map in front of the rectangles above
	
	for (int i=i_now;i<max_value_i;++i) {
		for (int j=j_now;j<max_value_j;++j) {
			if (getState(i,j) == GAME_EMPTY_CELL)
				continue;
			if (getState(i,j) == GAME_WALL) {
				boxSpr.SetPosition(w+(j%FIELD_SIZE)*IMAGE_SIZE,h+(i%FIELD_SIZE)*IMAGE_SIZE);
				app->Draw(boxSpr);
			}
			else if (getState(i,j) == GAME_PLAYER) {
			
				double rot = players.begin()->get()->rotation;
				
				gamerSpr.SetCenter(gamerImg.GetWidth()/2,gamerImg.GetHeight()/2);		
				gamerSpr.SetRotation(rot);
				gamerSpr.SetPosition(w+(j%FIELD_SIZE+0.5)*IMAGE_SIZE,h+(i%FIELD_SIZE+0.5)*IMAGE_SIZE);

				app->Draw(gamerSpr);			
			}			
			else if (getState(i,j) == GAME_ENEMY) {
				for(vector<PlayerPtr>::iterator it = players.begin()+1; it!=players.end(); ++it) {
					if (it->get()->getX() == i && it->get()->getY() == j) {
						double rot = it->get()->rotation;
						
						computerSpr.SetCenter(gamerImg.GetWidth()/2,gamerImg.GetHeight()/2);		
						computerSpr.SetRotation(rot);
						computerSpr.SetPosition(w+(j%FIELD_SIZE+0.5)*IMAGE_SIZE,h+(i%FIELD_SIZE+0.5)*IMAGE_SIZE);
				
						break;
					}
				}
				app->Draw(computerSpr);
			}
		}
	}
	app->Display();
}


/* checks path availability for every Ai player from it's start position to Gamer's position 
	returns true if every path is exist and false othewise */
bool Model::checkPaths() const {
	for(vector<PlayerPtr>::const_iterator it=players.begin()+1; it!=players.end(); ++it) {
		if (static_cast<Ai*>(it->get())->test_turn() == GAME_NO_WAY)
			return false;
	}
	return true;
}

/* Random generating walls on the map, using settings->walls parameter to control the frequency of walls */
void Model::createWalls() {
	srand( time (NULL) );	
	printf("Creating walls...");
	
	int chance = options->getSettings()->walls;
	
	switch (chance) {
		case 0:
			chance = 9;
			break;
		case 1:
			chance = 6;
			break;
		case 2:
			chance = 3;
	}
	
	for(int i=0;i<MAP_SIZE;i++)
		for(int j=0;j<MAP_SIZE;j++)		
			board[i][j] = (rand()%chance == 1) ? GAME_WALL : GAME_EMPTY_CELL;
	
	printf("Done\n");
}

/* Creates one Gamer and "computers" number of Ai */
void Model::createPlayers(const int &computers) {
	printf("Creating players...");
	
	players.clear();
	players.reserve(computers+1);

	addPlayer(new Gamer(this,0,0));		
	
	int w = MAP_SIZE-1, h = w;
	
	
	for (int i=0;i<computers;++i) {
		addPlayer(new Ai(this,w,h));
		
		printf("\nNew Ai added at: x=%d y=%d \n",w,h);	
		
		w -= FIELD_SIZE;
		
		if (w<0) {
			w = MAP_SIZE-1;
			h -= FIELD_SIZE;
			if (h<0)
				h = MAP_SIZE-2-i;
		}		
	}
					
	printf("Done\n");
}

/* Creates array for the map */
void Model::createWorld() {
	printf("Creating world...");
	
	board = new char* [MAP_SIZE];							//Creating map array
	for(int i=0;i<MAP_SIZE;++i)
		board[i] = new char [MAP_SIZE]();
		
	printf("Done\n");
}

Model::~Model() {

	for(int i=0;i<MAP_SIZE;++i)
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
	

