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

	g_red_host = SDLCommonFunc::LoadImage("red_host.png");
	if (g_red_host == NULL)
		return 0;
	 
	g_green_host = SDLCommonFunc::LoadImage("green_host.png");
	if (g_green_host == NULL)
		return 0;
	 
	g_die = SDLCommonFunc::LoadImage("die.png");
	if (g_die == NULL)
		return 0;

	g_win = SDLCommonFunc::LoadImage("win.png");
	if (g_win == NULL)
		return 0;

	MainObject human;
	human.SetRect(0, 250);
	bool ret = human.LoadImg("human.png");
	if (!ret)
		return 0;
	
	double bkgn_x = 0; //mây bay
	



	
	bool green_light = true; 
	int count = 0; 
	srand(time(0));
	int time = rand()%300; //số lần chạy vòng while để đổi đèn
	int X, Y;





	while (!is_quit){
		while (SDL_PollEvent(&g_even)){
			if (g_even.type == SDL_QUIT){
				is_quit = true;
				break;}

			human.HandleInputAction(g_even);
		}

		SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
	    //SDLCommonFunc::ApplySurface(g_host, g_screen, 1000, 128);
		
		// mây bay
		bkgn_x -= 0.2;
		SDLCommonFunc::ApplySurface(g_cloud, g_screen, bkgn_x, -10);
		SDLCommonFunc::ApplySurface(g_cloud, g_screen, bkgn_x + SCREEN_WIDTH, -10);
		if (bkgn_x <= -SCREEN_WIDTH)
			bkgn_x = 0;


		//đèn
		count ++;
		if (count == time){
			//đổi đèn
			if (green_light == true){X = human.rect_.x; Y = human.rect_.y;}
			green_light = !green_light;
			count = 0;
			time = rand()%300;
		}
		if (green_light == false){ //đèn đỏ
			if (count != 0 && (human.rect_.x != X || human.rect_.y != Y))
				SDLCommonFunc::ApplySurface(g_die, g_screen, 0, 0);
			
			    
		}

		if (green_light == false)
			SDLCommonFunc::ApplySurface(g_red_host, g_screen, 1000, 128);
		if (green_light == true)
			SDLCommonFunc::ApplySurface(g_green_host, g_screen, 1000, 128);

		if (human.rect_.x >= 940){ //win
			SDLCommonFunc::ApplySurface(g_win, g_screen, 0, 0);
		}


		human.Show(g_screen);
		human.HandleMove();

		if (SDL_Flip(g_screen) == -1)
			return 0;
	}
	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 0;
}