#ifndef LIGHT_H_
#define LIGHT_H_

#include "Mainobject.h"

enum GameStatus { PLAYING, WIN, LOSE };

double RandomNumber();              //Chọn thời gian đèn xanh: 1; 1.5; 2; 2.5 (s)
GameStatus CheckGameStatus(MainObject human, int check_time_remaining, Uint32 game_duration, bool green_light);

#endif
