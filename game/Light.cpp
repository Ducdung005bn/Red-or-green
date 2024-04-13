#include "Light.h"
#include "Common_Function.h"
#include "Text.h"

double RandomNumber(double green_light_time_array[], int n) { 
    srand(time(0));
    int randomIndex = rand() % n;
    return green_light_time_array[randomIndex];
}
void TimeRemaining(Uint32 game_duration, int check_time_remaining, SDL_Surface* des, TTF_Font* font){
	if (check_time_remaining >=0 && check_time_remaining <= game_duration){
	Text time;
	time.SetRect(450, 10);
	time.SetColor(Text::RED_TEXT);
	time.SetText("Time Remaining: " + std::to_string(check_time_remaining));
	time.CreateGameText(font, des);
	}
}
void CloudMovement(double& cloud_movement, SDL_Surface* src, SDL_Surface* des){
	cloud_movement -= 0.25;
	SDLCommonFunc::ApplySurface(src, des, cloud_movement, 0);
	SDLCommonFunc::ApplySurface(src, des, SCREEN_WIDTH + cloud_movement, 0);
	if (cloud_movement <= -SCREEN_WIDTH) cloud_movement = 0;
}
void ShowDoll(bool green_light, SDL_Surface* green_doll, SDL_Surface* red_doll, SDL_Surface* des){
	if (green_light == true)  SDLCommonFunc::ApplySurface(green_doll, des, 1000, 100);
	else if (green_light == false) SDLCommonFunc::ApplySurface(red_doll, des, 1000, 100);
}




