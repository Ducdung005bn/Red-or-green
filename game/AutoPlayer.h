#ifndef AUTO_PLAYER_H_
#define AUTO_PLAYER_H_

#include "Common_Function.h"
#include "Baseobject.h"
#include "Text.h"

class AutoPlayer : public BaseObject{
public:
	AutoPlayer();
	~AutoPlayer();
	void ShowAutoPlayer(SDL_Surface *des);
	void MoveAutoPlayer(bool any_guard_dead);
	void SetNotAlive(){alive = false;}
	bool GetAliveOrNot() {return alive;}
	void SetLastPosition(); 
	SDL_Rect GetLastPosition();


private:
	int x_val_;
	int y_val_;
	int picture_number;
	double picture_type;
	bool alive;
	SDL_Rect last_position; 

};

void SetRectForArrayOfAutoPlayers(AutoPlayer auto_player[], const int& numb_autoplayers);
void HandleAutoPlayer(AutoPlayer auto_player[], Text player_name[], const int& numb_autoplayers, const bool& any_guard_dead, SDL_Surface* des, TTF_Font* font);
bool CheckWin(int numb_guards_alive, int check_time_remaining, int game_duration);


#endif
