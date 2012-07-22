/*
	options model class
	
	(c) roman filippov, 2012
*/
#ifndef _OPTIONS_H_
#define _OPTIONS_H_
#define OPTIONS_FILENAME "config.rgc"
#define DEFAULT_FILENAME "default.rgc"
#include <string>
#include "applayer.h"
using std::string;
struct settings {
	int size;
	int walls;
	int enemies;
	bool fullscreen;
	bool edges;
};

class Application;

class Options : public AppLayer {
private:
	settings *s;
public:
	Options(Application *apl);
	~Options();
	void toDefaults();
	bool loadFromFile(const string &filename = DEFAULT_FILENAME);	
	void save(const string &filename = OPTIONS_FILENAME);
	settings *getSettings(); 
	void optionsScene();
};
#endif
