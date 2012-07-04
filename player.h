/*
	player model class
	
	(c) roman filippov, 2012
*/
#ifndef _PLAYER_H_
#define _PLAYER_H_
class Model;

class Player {
private:
	int x,y;		//Position
	Model *m;
	// - Something else (maybe health, e.t.c)
public:
	Player(Model *model,int &a,int &b);			//Initialize player on (a,b) position;
	bool moveTo(int &a,int &b);
	void setBoard(Model *b);
	
	int getX()const {			//inline
		return x;
	};
	int getY()const {
		return y;
	};
		
	virtual void turn()=0;
};

#endif
