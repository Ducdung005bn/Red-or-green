#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <Windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <algorithm>

const int SCREEN_WIDTH = 1099;
const int SCREEN_HEIGHT = 621;
const int SCREEN_BPP = 32;

//screen, background, ... chỉ load một lần nên không cần đưa vào lớp; static: biến tĩnh, chạy trong toàn bộ chương trình
static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Surface *g_poster = NULL;
static SDL_Surface *g_home = NULL;
static SDL_Surface *g_cloud = NULL;
static SDL_Surface *green_doll = NULL;
static SDL_Surface *red_doll = NULL;
static SDL_Surface *g_win = NULL;
static SDL_Surface *g_die = NULL; //nhân vật
static SDL_Surface *g_die_announcement; 
static SDL_Surface *g_how = NULL; 
static SDL_Surface *g_shop = NULL;
static SDL_Surface *g_confirm_purchase = NULL;

static Mix_Chunk* song1 = NULL;
static Mix_Chunk* song2 = NULL;
static Mix_Chunk* song3 = NULL;
static Mix_Chunk* song4 = NULL;
static Mix_Chunk* look_sound = NULL;
static Mix_Chunk* shot_sound = NULL;

static TTF_Font* g_font_text_1 = NULL; 
static TTF_Font* g_font_text_2 = NULL;
static TTF_Font* g_font_text_3 = NULL;
static TTF_Font* g_font_text_4 = NULL;
static TTF_Font* g_font_text_5 = NULL;
static TTF_Font* g_font_text_6 = NULL;


static SDL_Event g_event; //xử lí các sự kiện

namespace SDLCommonFunc{
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void CleanUp();
	int ShowMenu(SDL_Surface* des, TTF_Font* font1, TTF_Font* font2);
	int ShowHome(int total_coins, SDL_Surface* des, TTF_Font* font1, TTF_Font* font2);
	int ShowWin(int this_round_coins, int used_time, SDL_Surface* des, TTF_Font* font);
	int ShowDie(SDL_Surface* des, TTF_Font* font);
	int ShowShop(int& current_level, int& total_coins, SDL_Surface* des, TTF_Font* font1, TTF_Font* font2);
	int ConfirmPurchase(SDL_Surface* des, TTF_Font* font, int index, int price);
	bool MouseCheck(int mouse_x, int mouse_y, SDL_Rect input);
}

#endif
