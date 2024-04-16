﻿#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "Common_Function.h"

class BaseObject{
public:
	BaseObject();
	~BaseObject();
	void Show(SDL_Surface *des); //Lớp kế thừa mainobject viết hàm show riêng
	bool LoadImg(const char* file_name);
	void SetRect(const int& x, const int& y){rect_.x = x; rect_.y = y;}
	void SetFullRect(const int& x, const int& y, const int& w, const int& h) {rect_.x = x; rect_.y = y; rect_.w = w; rect_.h = h;}
	SDL_Rect GetRect() const {return rect_;}

protected: 
	SDL_Rect rect_;
	SDL_Surface *p_object_;
};

#endif
