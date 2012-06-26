/*
	exception class for game
	
	(c) roman filippov, 2012
*/
#ifndef _GAME_EXCEPT_H_
#define _GAME_EXCEPT_H_
#include <stdexcept>
#include <string>

class GameException : public std::logic_error {
public:
	GameException(const std::string &arg);
};

#endif
