#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "Common_Function.h"
#include "Text.h"

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font1, TTF_Font* font2);
int SDLCommonFunc::ShowHome(SDL_Surface* des, TTF_Font* font1, TTF_Font* font2);
int SDLCommonFunc::ShowWin(SDL_Surface* des, TTF_Font* font);

#endif
