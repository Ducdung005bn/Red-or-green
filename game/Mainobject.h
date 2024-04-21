#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "Baseobject.h"
#include "Common_Function.h"

#define WIDTH_MAIN_OBJECT 75
#define HEIGHT_MAIN_OBJECT 180

class MainObject : public BaseObject{
public:
	MainObject();
	~MainObject();
	void HandleInputAction(SDL_Event events);
	void HandleMove();
	void ShowMainObject(SDL_Surface *des);
	void SetPicture(std::string clothes_type, int picture_number);
	void SetLastPosition(); 
	SDL_Rect GetLastPosition();
	void SetSpeed(const int& x) {speed = x;}

private:
	int x_val_;
	int y_val_;
	double picture_type;
	std::string clothes_type; //tên đường dẫn tới tranh = clothes_type + picture_type
	int picture_number; //số lượng tranh tạo animation
	SDL_Rect last_position; 
	int speed;
};

#endif
