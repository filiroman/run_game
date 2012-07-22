/*
	application_layer (base class for components-to-application connection) model class
	
	(c) roman filippov, 2012
*/
#ifndef _APP_LAYER_H_
#define _APP_LAYER_H_
class Application;

class AppLayer {
protected:
	Application *app;
public:
	AppLayer(Application *apl);
	~AppLayer();
};

#endif

