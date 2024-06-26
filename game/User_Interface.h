#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

#include "Common_Function.h"
#include "Text.h"

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font1, TTF_Font* font2);
int SDLCommonFunc::ShowHome(int current_level, int total_coins, SDL_Surface* des, TTF_Font* font1, TTF_Font* font2);
int SDLCommonFunc::ShowWin(int this_round_coins, int used_time, SDL_Surface* des, TTF_Font* font);
int SDLCommonFunc::ShowDie(SDL_Surface* des, TTF_Font* font);
int SDLCommonFunc::ShowShop(int& current_level, int& total_coins, SDL_Surface* des, TTF_Font* font1, TTF_Font* font2);
int SDLCommonFunc::ConfirmPurchase(SDL_Surface* des, TTF_Font* font, int index, int price);
bool SDLCommonFunc::MouseCheck(int mouse_x, int mouse_y, SDL_Rect input);
int SDLCommonFunc::ShowNeedToUpgrade(SDL_Surface* des, TTF_Font* font);
int SDLCommonFunc::ShowExploreLastStand(SDL_Surface* des, TTF_Font* font);
int SDLCommonFunc::ShowWinLastStand(SDL_Surface* des, TTF_Font* font);






#endif
