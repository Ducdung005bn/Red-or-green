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
void PlaySong(Uint32 green_light_time, double green_light_time_array[], int n){
	song1 = Mix_LoadWAV("song1.wav");
	song2 = Mix_LoadWAV("song2.wav");
	song3 = Mix_LoadWAV("song3.wav");
	song4 = Mix_LoadWAV("song4.wav");
	if (song1 == NULL || song2 == NULL || song3 == NULL || song4 == NULL) 
	return;
    if (green_light_time == green_light_time_array[0]*1000) Mix_PlayChannel(-1, song1, 0); 
    else if (green_light_time == green_light_time_array[1]*1000) Mix_PlayChannel(-1, song2, 0); 
	else if (green_light_time == green_light_time_array[2]*1000) Mix_PlayChannel(-1, song3, 0); 
	else if (green_light_time == green_light_time_array[3]*1000) Mix_PlayChannel(-1, song4, 0); 
}
void DisplayObjectsBasedOnLevel(const int& current_level, MainObject &human, Follower &guard_1, Follower &guard_2, SDL_Surface* des) {
    if (current_level == 1) {
        human.ShowMainObject(des);
    } else if (current_level == 2) {
        if (human.GetRect().y + human.GetRect().h >= guard_1.GetRect().y + guard_1.GetRect().h) {
            guard_1.ShowFollower(des);
            human.ShowMainObject(des);
        } else {
            human.ShowMainObject(des);
            guard_1.ShowFollower(des);
        }
    } else if (current_level == 3) {
        int human_value = human.GetRect().y + human.GetRect().h;
        int guard_1_value = guard_1.GetRect().y + guard_1.GetRect().h;
        int guard_2_value = guard_2.GetRect().y + guard_2.GetRect().h;
        int min_value = min(min(human_value, guard_1_value), guard_2_value);
        if (min_value == human_value) {
            human.ShowMainObject(des);
            if (guard_2_value < guard_1_value) {
                guard_2.ShowFollower(des);
                guard_1.ShowFollower(des);
            } else {
                guard_1.ShowFollower(des);
                guard_2.ShowFollower(des);
            }
        } else if (min_value == guard_1_value) {
            guard_1.ShowFollower(des);
            if (human_value < guard_2_value) {
                human.ShowMainObject(des);
                guard_2.ShowFollower(des);
            } else {
                guard_2.ShowFollower(des);
                human.ShowMainObject(des);
            }
        } else {
            guard_2.ShowFollower(des);
            if (human_value < guard_1_value) {
                human.ShowMainObject(des);
                guard_1.ShowFollower(des);
            } else {
                guard_1.ShowFollower(des);
                human.ShowMainObject(des);
            }
        }
    }
}
void CheckCollisionBasedOnLevel(bool& check_collision, const int& current_level, const Follower& guard_1, const Follower& guard_2, const MainObject& human){
    switch(current_level) {
        case 2:
            check_collision = guard_1.CheckCollisionWithHuman(human.GetRect());
            break;
        case 3:
            check_collision = guard_1.CheckCollisionWithHuman(human.GetRect());
            if (!check_collision) {
                check_collision = guard_2.CheckCollisionWithHuman(human.GetRect());
            }
            break;
        default:
            break;
    }
}







