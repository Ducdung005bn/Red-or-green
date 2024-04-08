#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Baseobject.h"
#include "Common_Function.h"

#define WIDTH_MAIN_OBJECT 60
#define HEIGHT_MAIN_OBJECT 190

class MainObject : public BaseObject{
public:
	MainObject();
	~MainObject();
	void HandleInputAction(SDL_Event events);
	void HandleMove();
	void ShowMainObject(SDL_Surface *des);

private:
	int x_val_;
	int y_val_;
	double picture_type;

};

#endif
