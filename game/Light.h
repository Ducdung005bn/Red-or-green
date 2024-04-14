#ifndef LIGHT_H_
#define LIGHT_H_

#include "Mainobject.h"

double RandomNumber (double green_light_time_array[], int n);              //Chọn thời gian đèn xanh
void TimeRemaining(Uint32 game_duration, int check_time_remaining, SDL_Surface* des, TTF_Font* font); 
void CloudMovement(double& cloud_movement, SDL_Surface* src, SDL_Surface* des);
void ShowDoll(bool green_light, SDL_Surface* green_doll, SDL_Surface* red_doll, SDL_Surface* des);
void PlaySong(Uint32 green_light_time, double green_light_time_array[], int n);

#endif
