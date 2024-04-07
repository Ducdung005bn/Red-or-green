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