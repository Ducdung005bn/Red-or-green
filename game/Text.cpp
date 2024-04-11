#include "Text.h"

Text::Text(){
	rect_.x = 450;
	rect_.y = 10;
}

Text::~Text(){

}

void Text::SetColor(const int& type){
	if (type == RED_TEXT){
		SDL_Color color = {255, 0, 0};
		text_color_ = color;
	}
	else if (type == WHITE_TEXT){
		SDL_Color color = {255, 255, 255};
		text_color_ = color;
	}
	else if (type == GREEN_TEXT){
		SDL_Color color = {0, 128, 0};
		text_color_ = color;
	}
	else if (type == YELLOW_TEXT){
		SDL_Color color = {255, 255, 0};
		text_color_ = color;
	}
	else if (type == NAVY_TEXT){
		SDL_Color color = {0, 0, 128};
		text_color_ = color;
	}
	else { //màu đen
		SDL_Color color = {0, 0, 0};
		text_color_ = color;
	}
}

void Text::CreateGameText(TTF_Font* font, SDL_Surface* des){
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	Show(des);
}