#ifndef WHEEL_H_
#define WHEEL_H_

#include "Common_Function.h"
#include "Text.h"

Uint32 getPixel(SDL_Surface* surface, int x, int y);
void putPixel(SDL_Surface* surface, int x, int y, Uint32 pixel);
SDL_Surface* rotateSurface(SDL_Surface* src, double angle);
int calculateSelectedSector(double rotationAngle);
int SDLCommonFunc::ShowGameOfChance(SDL_Surface* des, TTF_Font* font);


#endif
