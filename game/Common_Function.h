#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


#include <cstdlib>
#include <ctime>





const int SCREEN_WIDTH = 1099;
const int SCREEN_HEIGHT = 621;
const int SCREEN_BPP = 32;

static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Surface *g_cloud = NULL;
static SDL_Surface *g_red_host = NULL; 
static SDL_Surface *g_green_host = NULL; 
static SDL_Surface *g_die = NULL; 
static SDL_Surface *g_win = NULL; 

static SDL_Event g_even;

namespace SDLCommonFunc{
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void CleanUp();
}

#endif
