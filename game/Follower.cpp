#include "Follower.h"

Follower::Follower(){
	x_val_ = 0;
	y_val_ = 0;
	picture_number = 7;
	picture_type = 1;
	previous_position.x = 0;
	previous_position.y = 0;

}
Follower::~Follower(){
	//To do
}
void Follower::ShowFollower(SDL_Surface *des){
	double animation_speed = 0.25/4;

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
void Follower::MoveFollower(SDL_Rect human, bool green_light) {

    if (green_light) {
        int follower_center_x = rect_.x + rect_.w / 2;
        int follower_center_y = rect_.y + rect_.h;

        int human_center_x = human.x + human.w / 2;
        int human_center_y = human.y + human.h;

        int dx = human_center_x - follower_center_x;
        int dy = human_center_y - follower_center_y;

        double distance = sqrt(dx * dx + dy * dy);
        double unit_x = dx / distance;
        double unit_y = dy / distance;

        double speed = 2.0; // Adjust speed as needed

        x_val_ = static_cast<int>(speed * unit_x);
        y_val_ = static_cast<int>(speed * unit_y);

        rect_.x += x_val_;
        rect_.y += y_val_;

        // Nếu đèn xanh nhưng human đứng yên nên follower đứng yên, thì đặt x_val_ = y_val_ = 0 để không tạo animation
        if (GetPreviousPosition().x != rect_.x || GetPreviousPosition().y != rect_.y) {
            SetPreviousPosition(rect_.x, rect_.y); // Update previous position
        } else {
            x_val_ = 0;
			y_val_ = 0;
        }
    } 
	else {
        x_val_ = 0;
        y_val_ = 0;
    }
}
