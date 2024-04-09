#include "Light.h"
#include "Common_Function.h"

double RandomNumber() { 
    srand(time(0));
    int randomIndex = rand() % 4;
    double numberArray[] = {1.6, 2, 2.5, 3};
    return numberArray[randomIndex];
}
GameStatus CheckGameStatus(MainObject human, int check_time_remaining, Uint32 game_duration, bool green_light){
	if (human.GetRect().x < 940 && check_time_remaining < 0){
		return LOSE;
	}
	if (human.GetRect().x >= 940){ 
		return WIN;
	}
	if ((human.GetRect().x != human.GetLastPosition().x || human.GetRect().y != human.GetLastPosition().y) 
		&& green_light == false){
		return LOSE;
	}
	return PLAYING;
}

