#include "Follower.h"

Follower::Follower(){
	x_val_ = 0;
	y_val_ = 0;
	picture_number = 7;
	picture_type = 1;
}
Follower::~Follower(){
	//To do
}
void Follower::ShowFollower(SDL_Surface *des){
	double animation_speed = 0.25/4;

	for (int i = 1; i <= picture_number; i++){
		if (picture_type == i) 
			p_object_ = SDLCommonFunc::LoadImage("guard_" + std::to_string((int)picture_type) + ".png"); 
	}
	
	if (x_val_ != 0 || y_val_ != 0){
		if (picture_type < picture_number)
			picture_type += animation_speed;
		else if (picture_type == picture_number)
			picture_type = 1;
	}
	SDLCommonFunc::ApplySurface(p_object_, des, rect_.x, rect_.y);
}