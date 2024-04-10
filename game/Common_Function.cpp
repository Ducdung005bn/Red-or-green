#include "Common_Function.h"

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

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font){ //trả chỉ số chọn item
	g_poster = LoadImage("poster.png");
	if (g_poster == NULL) return 1; //1 là exit
	
	const int menu_item_number = 2;
	SDL_Rect item_position[menu_item_number];
	item_position[0].x = 100; item_position[0].y = 100; item_position[0].w = 100 ;item_position[0].h = 100; 
	item_position[1].x = 500; item_position[1].y = 100; item_position[1].w = 100 ;item_position[1].h = 100; 

	Text text_menu[2];
	text_menu[0].SetText("Play");
	text_menu[0].SetColor(Text::BLACK_TEXT);
	text_menu[0].SetRect(item_position[0].x, item_position[0].y);

	text_menu[1].SetText("Exit");
	text_menu[1].SetColor(Text::BLACK_TEXT);
	text_menu[1].SetRect(item_position[1].x, item_position[1].y);


}
