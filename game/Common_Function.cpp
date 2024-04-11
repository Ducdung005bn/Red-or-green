﻿#include "Common_Function.h"
#include "Text.h"

SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path){ 
  SDL_Surface *load_image = NULL;
  SDL_Surface *optimize_image = NULL;
  load_image = IMG_Load(file_path.c_str());
  if (load_image != NULL)
  {
	optimize_image = SDL_DisplayFormat(load_image);
    SDL_FreeSurface(load_image); //dữ liệu ở trong optimize_image nên giải phóng load_image
	if (optimize_image != NULL) {
		UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0, 0); //0 0 0 là màu đen
		SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);}
  }
  return optimize_image;
}

void SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y){ //đặt nguồn -> đích ở vị trí x, y
  SDL_Rect offset;
  offset.x = x; offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset);
}

void SDLCommonFunc::CleanUp(){ //giải phóng vùng nhớ
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font1, TTF_Font* font2){ //trả chỉ số chọn item
	g_poster = LoadImage("poster.png");
	if (g_poster == NULL) return 1; //1 là exit
	
	const int menu_item_number = 2;
	SDL_Rect item_position[menu_item_number];
	item_position[0].x = 120; item_position[0].y = 100; item_position[0].w = 101 ;item_position[0].h = 47; 
	item_position[1].x = 900; item_position[1].y = 100; item_position[1].w = 87 ;item_position[1].h = 44; 

	Text text_menu[2];
	text_menu[0].SetText("PLAY");
	text_menu[0].SetColor(Text::BLACK_TEXT);
	text_menu[0].SetRect(item_position[0].x, item_position[0].y);

	text_menu[1].SetText("EXIT");
	text_menu[1].SetColor(Text::BLACK_TEXT);
	text_menu[1].SetRect(item_position[1].x, item_position[1].y);

	static TTF_Font* current_font[2];
	current_font[0] = font1; current_font[1] = font1;

	bool selected[menu_item_number] = {0};

	int mouse_x = 0, mouse_y = 0;

	SDL_Event m_event;
	while(true){
		SDLCommonFunc::ApplySurface(g_poster, des, 0, 0);

		for (int i = 0; i < menu_item_number; i++){
			text_menu[i].CreateGameText(current_font[i], des);
		}
		while (SDL_PollEvent(&m_event)){
			switch(m_event.type){
			case SDL_QUIT: return 1; //1 là exit
			case SDL_MOUSEMOTION:
				{
					mouse_x = m_event.motion.x;
					mouse_y = m_event.motion.y;
					
					for (int i = 0; i < menu_item_number; i++){
						if (mouse_x >= item_position[i].x
					     && mouse_y >= item_position[i].y
						 && mouse_y <= item_position[i].y + item_position[i].h
						 && mouse_x <= item_position[i].x + item_position[i].w)
						{
							//nhấp chuột qua, chưa chọn (màu đen) thành chọn (màu đỏ). Nếu chọn rồi (màu đỏ) thì giữ nguyên
							if (selected[i] == false) 
							{
								selected[i] = 1;
								text_menu[i].SetColor(Text::RED_TEXT);
								current_font[i] = font2;
							}
						}
						else
						{
							//chuột không qua, chưa chọn (màu đen) giữ nguyên. Nếu chọn rồi thì thành chưa chọn (màu đen)
							if (selected[i] == true)
							{
								selected[i] = 0;
								text_menu[i].SetColor(Text::BLACK_TEXT);
								current_font[i] = font1;
							}
						}	 
					} //kết thúc vòng for
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
					mouse_x = m_event.button.x;
					mouse_y = m_event.button.y;
					for (int i = 0; i < menu_item_number; i++){
						if (mouse_x >= item_position[i].x
						 && mouse_y >= item_position[i].y
						 && mouse_y <= item_position[i].y + item_position[i].h
						 && mouse_x <= item_position[i].x + item_position[i].w)
						return i;
					} 
					break;
				}
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
					return 1;
			default: break;
			} //kết thúc switch
		} //kết thúc while
		SDL_Flip(des);
	}//kết thúc while
	return 1;
}
int SDLCommonFunc::ShowHome(SDL_Surface* des, TTF_Font* font1, TTF_Font* font2){
	g_home = LoadImage("home.png");
	if (g_home == NULL) return -1;
	const int home_item_number = 5;
	SDL_Rect item_position[home_item_number];
	item_position[0].x = 40 ; item_position[0].y = 10 ; item_position[0].w = 86 ; item_position[0].h = 30 ;
	item_position[1].x = 590 ; item_position[1].y = 59 ; item_position[1].w = 200; item_position[1].h = 35;
	item_position[2].x = 590; item_position[2].y = 129; item_position[2].w = 200; item_position[2].h = 35;
	item_position[3].x = 590; item_position[3].y = 198; item_position[3].w = 200; item_position[3].h = 30;
	item_position[4].x = 590; item_position[4].y = 265; item_position[4].w = 200; item_position[4].h = 30;

	Text text_home[home_item_number];
	text_home[0].SetText("Return");
	text_home[1].SetText("Shop");
	text_home[2].SetText("Start game");
	text_home[3].SetText("Instructions");
	text_home[4].SetText("Last stand");

	for (int i = 0; i < home_item_number; i++){
		text_home[i].SetColor(Text::BLACK_TEXT);
		text_home[i].SetRect(item_position[i].x, item_position[i].y);
	}



	bool selected[home_item_number] = {0};
	int current_home_picture = 0, last_home_picture = 0;
	int mouse_x = 0, mouse_y = 0;
	SDL_Event m_event;

	while(true){
		if (current_home_picture != last_home_picture){
		switch(current_home_picture){
		case 0: g_home = LoadImage("home.png"); break;
		case 1: g_home = LoadImage("home1.png"); break;
		case 2: g_home = LoadImage("home2.png"); break;
		case 3: g_home = LoadImage("home3.png"); break;
		case 4: g_home = LoadImage("home4.png"); break;
		}
		if (g_home == NULL) return -1;
		}
		
		SDLCommonFunc::ApplySurface(g_home, des, 0, 0);
		for (int i = 1; i < home_item_number; i++){
			text_home[i].CreateGameText(font1, des);
		}
			text_home[0].CreateGameText(font2, des);

		last_home_picture = current_home_picture;

		while (SDL_PollEvent(&m_event)){
			switch(m_event.type){
			case SDL_QUIT: return -1;
			case SDL_MOUSEMOTION:
				{
					mouse_x = m_event.motion.x;
					mouse_y = m_event.motion.y;
					for (int i = 0; i < home_item_number; i++){
						if (mouse_x >= item_position[i].x 
						 && mouse_y >= item_position[i].y 
						 && mouse_y <= item_position[i].y + item_position[i].h
						 && mouse_x <= item_position[i].x + item_position[i].w)
						{
							if (selected[i] == false)
							{
								selected[i] = true;
								text_home[i].SetColor(Text::RED_TEXT);
								if (i != 0) current_home_picture = i;
							}
						}
						else
						{
							if (selected[i] == true)
							{
								selected[i] = false;
								text_home[i].SetColor(Text::BLACK_TEXT);
								if (i != 0) current_home_picture = 0;
							}
						}
					}
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
					mouse_x = m_event.button.x;
					mouse_y = m_event.button.y;
                        for (int i = 0; i < home_item_number; i++){
						if (mouse_x >= item_position[i].x
						 && mouse_y >= item_position[i].y
						 && mouse_y <= item_position[i].y + item_position[i].h
						 && mouse_x <= item_position[i].x + item_position[i].w)
						 return i;
						}
					break;
				}
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
					return -1;
			default: break;
			}

		}
		SDL_Flip(des);
	}
	return -1;
}


