/*
	main game model class
	
	(c) roman filippov, 2012
*/
#ifndef _MODEL_H_
#define _MODEL_H_
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <cstring>
#include "player.h"
#include "view.h"
#include "gameexception.h"
#include "options.h"
#include "applayer.h"

/* map cells state defines (returned by model->getState)*/
#define GAME_WALL '3'
#define GAME_ENEMY '2'
#define GAME_PLAYER '1'
#define GAME_EMPTY_CELL '0'

/* defines Game window header */
#define GAME_WINDOW_NAME "Run Game"

/* resources folder macro define */
#define GAME_RESOURCES(name) "resources/"#name

/* predeclarations of Model used classes */
class Menu;
class Ai;
//class View;
class Application;

using std::vector;
using std::pair;
using std::string;

/* Smart pointers from boost library, used to keep pointers to Players in container */
typedef boost::shared_ptr<Player> PlayerPtr;

class Model : public AppLayer {
private:
	//Fields
	Options *options;
	char **board;		//Game Board
	const View *view;
	vector<PlayerPtr> players;
	int FIELD_SIZE;	//Size for map to draw in one screen
	int MAP_SIZE;		//Real size of all map
	sf::Image gamerImg,computerImg,boxImg,cellImg;
	sf::Sprite gamerSpr,computerSpr,boxSpr,cellSpr;
	
	//Methods
	void createWorld();
	void createWalls();
	void createPlayers(int computers=1);
public:
	Model(Application *apl, Options *opt);
	~Model();
	bool checkRange(const int &x,const int &y) const;
	bool addPlayer(Player *p);
	char getState(int x,int y) const;
	void setState(int &x,int &y,char state);
	bool checkPaths() const;
	int step();
	void drawMap();
	pair<int,int> getPlayerPosition() const;
	friend class Gamer;
	friend class Ai;
	friend class Application;
};

inline pair<int,int> Model::getPlayerPosition() const {
	return std::make_pair(players.begin()->get()->getX(),players.begin()->get()->getY());
}

inline bool Model::checkRange(const int &x,const int &y) const {

	if (x<0 || y<0 || x>=MAP_SIZE || y>=MAP_SIZE)
		return false;
	return true;
}

inline char Model::getState(int x,int y) const {
	if (checkRange(x,y)) {
		return board[x][y];
	}
	else
		throw new GameException("wrong coordinates to check");
}

inline void Model::setState(int &x,int &y,char state) {
	if (checkRange(x,y))
		board[x][y] = state;
	else
		throw new GameException("wrong coordinates to set state");
}

#endif
