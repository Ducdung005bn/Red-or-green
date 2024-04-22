#include "AutoPlayer.h"
AutoPlayer::AutoPlayer(){
	srand(time(NULL));
	x_val_ = 0;
	y_val_ = 0;
	picture_number = 7;
	picture_type = 1;
	alive = true;
}
AutoPlayer::~AutoPlayer(){
	//To do
}

void AutoPlayer::ShowAutoPlayer(SDL_Surface *des) {
	if (alive){
		double animation_speed = 0.25/2;
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
}

void AutoPlayer::MoveAutoPlayer(){
	if (alive){
	x_val_ = rand() % 2; //0, 1
	rect_.x += x_val_;
	}
}