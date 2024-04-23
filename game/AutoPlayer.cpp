#include "AutoPlayer.h"
AutoPlayer::AutoPlayer(){
	srand(time(NULL));
	x_val_ = 0;
	y_val_ = 0;
	picture_number = 7;
	picture_type = 1;
	alive = true;
	last_position.x = 0;
	last_position.y = 0;
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

void AutoPlayer::MoveAutoPlayer(bool any_guard_dead){
	if (!any_guard_dead){
		if (alive){
			x_val_ = rand() % 2; //0, 1
			rect_.x += x_val_;
		}
	}
}
void AutoPlayer::SetLastPosition(){
	last_position.x = rect_.x;
	last_position.y = rect_.y;
}
SDL_Rect AutoPlayer::GetLastPosition(){
	return last_position;
}
void SetRectForArrayOfAutoPlayers(AutoPlayer auto_player[], const int& numb_autoplayers){
	for (int i = 0; i < numb_autoplayers; i++){
		if (i%2 == 0)
		auto_player[i].SetRect(0, 240 + i*20);
		else
		auto_player[i].SetRect(60, 240 + i*20);
	}
}
void HandleAutoPlayer(AutoPlayer auto_player[], Text player_name[], const int& numb_autoplayers, const bool& any_guard_dead, SDL_Surface* des, TTF_Font* font){
	for (int i = 0; i < numb_autoplayers; i++){
		if(auto_player[i].GetAliveOrNot() == true){
			auto_player[i].MoveAutoPlayer(any_guard_dead);
			auto_player[i].ShowAutoPlayer(des);
			player_name[i].SetRect(auto_player[i].GetRect().x, auto_player[i].GetRect().y - 20);
			player_name[i].CreateGameText(font, des);
			}
		}
}
bool CheckWin(int numb_guards_alive, int check_time_remaining, int game_duration) {
    return (numb_guards_alive == 0 && check_time_remaining >= 0 && check_time_remaining <= game_duration) ||
           (numb_guards_alive > 0 && check_time_remaining < 0);
}
