#include "Mainobject.h"
#include "Common_Function.h"

MainObject::MainObject(){
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
	picture_type = 1;
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
void MainObject::ShowMainObject(SDL_Surface *des){
	double animation_speed = 0.125;

	for (int i = 1; i <= picture_number; i++){
		if (picture_type == i)
			p_object_ = SDLCommonFunc::LoadImage(picture_link + std::to_string((int)picture_type) + ".png"); 
	}
	
	if (x_val_ != 0 || y_val_ != 0){
		if (picture_type < picture_number)
			picture_type += animation_speed;
		else if (picture_type == picture_number)
			picture_type = 1;
	}
	SDLCommonFunc::ApplySurface(p_object_, des, rect_.x, rect_.y);
}
void MainObject::SetPicture(std::string p_link, int p_number){
	picture_link = p_link;
	picture_number = p_number;
}

