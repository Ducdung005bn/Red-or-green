#ifndef AUTO_PLAYER_H_
#define AUTO_PLAYER_H_

#include "Common_Function.h"
#include "Baseobject.h"

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


#endif
