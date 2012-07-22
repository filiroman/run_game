/*
	application_layer (base class for components-to-application connection) model class
	
	(c) roman filippov, 2012
*/
#include "applayer.h"
#include <cstdlib>

AppLayer::AppLayer(Application *apl) : app(apl) {};

AppLayer::~AppLayer() {
	app = NULL;
}
