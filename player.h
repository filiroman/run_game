/*
	player model class
	
	(c) roman filippov, 2012
*/
#ifndef _PLAYER_H_
#define _PLAYER_H_
class Model;

class Player {
protected:
	int x,y;		//Position
	Model *m;
	// - Something else (maybe health, e.t.c)
public:
	Player(Model *model,int a,int b);			//Initialize player on (a,b) position;
	bool moveTo(const int a,const int b);
	void setBoard(Model *b);
	
	int getX()const {			//inline
		return x;
	};
	int getY()const {
		return y;
	};
		
	virtual int turn(){};
};

#endif
