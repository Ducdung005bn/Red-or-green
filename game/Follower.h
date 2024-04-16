#ifndef FOLLOWER_H_
#define FOLLOWER_H_

#include "Common_Function.h"
#include "Baseobject.h"

class Follower : public BaseObject{
public:
	Follower();
	~Follower();
	void ShowFollower(SDL_Surface *des);

private:
	int x_val_;
	int y_val_;
	int picture_number; //to create animation
	double picture_type;
};




#endif
