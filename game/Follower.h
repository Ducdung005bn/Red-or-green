#ifndef FOLLOWER_H_
#define FOLLOWER_H_

#include "Common_Function.h"
#include "Baseobject.h"

class Follower : public BaseObject{
public:
	Follower();
	~Follower();
	void ShowFollower(SDL_Surface *des);
	void MoveFollower(SDL_Rect human, bool green_light);
	void SetPreviousPosition(const int& x, const int& y){
		previous_position.x = x;
		previous_position.y = y;
	}
	SDL_Rect GetPreviousPosition(){return previous_position;}


private:
	int x_val_;
	int y_val_;
	SDL_Rect previous_position;
	int picture_number; //to create animation
	double picture_type;
};




#endif
