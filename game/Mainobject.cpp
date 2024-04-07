#include "Mainobject.h"

MainObject::MainObject(){
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}
MainObject::~MainObject(){
	//to do
}
void MainObject::HandleInputAction(SDL_Event events){
	if (events.type == SDL_KEYDOWN){    //phím nhấn xuống
	switch (events.key.keysym.sym){
	case SDLK_UP:    y_val_ -= 1; break;
	case SDLK_DOWN:  y_val_ += 1; break;
	case SDLK_RIGHT: x_val_ += 1; break;
	case SDLK_LEFT:  x_val_ -= 1; break;}
	}
	else if (events.type == SDL_KEYUP){ //phím nhả ra
	switch (events.key.keysym.sym){
	case SDLK_UP:    y_val_ += 1; break;
	case SDLK_DOWN:  y_val_ -= 1; break;
	case SDLK_RIGHT: x_val_ -= 1; break;
	case SDLK_LEFT:  x_val_ += 1; break;}
	}
}
void MainObject::HandleMove(){
	rect_.x += x_val_;
	if (rect_.x < 0 || rect_.x > 948)
		rect_.x -= x_val_;

	rect_.y += y_val_;
	if (rect_.y < 175 || rect_.y > 390)
		rect_.y -= y_val_;
}