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
	void SetPicture(std::string picture_link, int picture_number);
	void SetLastPosition(); 
	SDL_Rect GetLastPosition();

private:
	int x_val_;
	int y_val_;
	double picture_type;
	std::string picture_link; //đường dẫn tới tranh
	int picture_number; //số lượng tranh tạo animation
	SDL_Rect last_position; //lưu vị trí người chơi khi hết đèn xanh (để kiểm tra di chuyển không)
};

#endif
