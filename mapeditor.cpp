/*
	map editor model class
	
	(c) roman filippov, 2012
*/
#include "mapeditor.h"
#include "menu.h"
#include <vector>
#include <string>

using std::string;

MapEditor::MapEditor(Application *apl) : AppLayer(apl) {
}

void MapEditor::show()const {
	std::vector<string> menuItems = new std::vector<string>();
	menuItems.push_back("Map Size");
	Menu *m = new Menu(app,menuItems);
	m->show();
	delete m;
}
