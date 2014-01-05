/*
	map editor model class
	
	(c) roman filippov, 2012
*/
#ifndef _MAPEDIT_H_
#define _MAPEDIT_H_
#include "applayer.h"

class MapEditor : public AppLayer {
public:
	MapEditor(Application *apl);
	void show()const;
};


#endif
