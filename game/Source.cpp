#include "Common_Function.h"
#include "Mainobject.h"

bool Init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

	if (g_screen == NULL)
		return false;
	return true;
}

int main(int arc, char*argv[]){	

	bool is_quit = false;
	if (Init() == false)
		return 0;
	
	g_bkground = SDLCommonFunc::LoadImage("1background.png");
	if (g_bkground == NULL)
		return 0;

	g_cloud = SDLCommonFunc::LoadImage("cloudfly.png");
	if (g_cloud == NULL)
		return 0;

	g_host = SDLCommonFunc::LoadImage("host.png");
	if (g_host == NULL)
		return 0;

	MainObject human;
	human.SetRect(0, 250);
	bool ret = human.LoadImg("human.png");
	if (!ret)
		return 0;
	
	double bkgn_x = 0; //mây bay

	while (!is_quit){
		while (SDL_PollEvent(&g_even)){
			if (g_even.type == SDL_QUIT){
				is_quit = true;
				break;}

			human.HandleInputAction(g_even);
		}

		SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
		SDLCommonFunc::ApplySurface(g_host, g_screen, 1000, 125);
		
		// mây bay
		bkgn_x -= 0.2;
		SDLCommonFunc::ApplySurface(g_cloud, g_screen, bkgn_x, 0);
		SDLCommonFunc::ApplySurface(g_cloud, g_screen, bkgn_x + SCREEN_WIDTH, 0);
		if (bkgn_x <= -SCREEN_WIDTH)
			bkgn_x = 0;

		human.Show(g_screen);
		human.HandleMove();

		if (SDL_Flip(g_screen) == -1)
			return 0;
	}
	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 0;
}