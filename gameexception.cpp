/*
	exception class for game
	
	(c) filippov roman, 2012
*/

#include "gameexception.h"

GameException::GameException(const std::string &arg):std::logic_error(arg){ }
