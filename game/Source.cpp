#include "Common_Function.h"
#include "Mainobject.h"
#include "Light.h"


bool Init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); //định dạng màn hình
	if (g_screen == NULL) return false;

	//Khởi tạo audio
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;
	song_1_5 = Mix_LoadWAV("song_1_5.wav");
	song_2 = Mix_LoadWAV("song_2.wav");
	song_2_5 = Mix_LoadWAV("song_2_5.wav");
	song_3 = Mix_LoadWAV("song_3.wav");
	if (song_1_5 == NULL || song_2 == NULL || song_2_5 == NULL || song_3 == NULL) return false;

	return true;
}

int main(int arc, char*argv[]){
	bool is_quit = false;
	if (Init() == false) return 0;
	
	g_bkground = SDLCommonFunc::LoadImage("p.background.png"); if (g_bkground == NULL) return 0;
	g_cloud    = SDLCommonFunc::LoadImage("p.cloud.png"); if (g_cloud == NULL) return 0; 
	double cloud_movement = 0;
	green_doll = SDLCommonFunc::LoadImage("p.green_doll.png"); if (green_doll == NULL) return 0;
	red_doll   = SDLCommonFunc::LoadImage("p.red_doll.png"); if (red_doll == NULL) return 0;


	MainObject human;
	human.SetRect(0, 250);
	bool ret = human.LoadImg("p.human.png");
	if (!ret) return 0;

	bool green_light = true; 
	Uint32 start_green = 0, start_red = 0;
	Uint32 green_light_time; //mili giây
	bool handle_green_light = false; //đèn xanh đã được xử lí chưa?

	Uint32 time_value; 

	while (!is_quit){
		while (SDL_PollEvent(&g_even)){
			if (g_even.type == SDL_QUIT){
				is_quit = true;
				break;}
			human.HandleInputAction(g_even);
		}
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);

		//cloud_movement
		cloud_movement -= 0.25;
		SDLCommonFunc::ApplySurface(g_cloud, g_screen, cloud_movement, 0);
		SDLCommonFunc::ApplySurface(g_cloud, g_screen, SCREEN_WIDTH + cloud_movement, 0);
		if (cloud_movement <= -SCREEN_WIDTH) cloud_movement = 0;

		time_value = SDL_GetTicks();

		if (!handle_green_light && time_value >= start_green){ //bắt đầu đèn xanh
			green_light_time = RandomNumber()*1000;
			start_red = start_green + green_light_time;     //cài đặt thời gian đèn đỏ tiếp theo
			green_light = true;
			switch(green_light_time){
			case 1500: Mix_PlayChannel(-1, song_1_5, 0); break;
			case 2000: Mix_PlayChannel(-1, song_2, 0); break;
			case 2500: Mix_PlayChannel(-1, song_2_5, 0); break;
			case 3000: Mix_PlayChannel(-1, song_3, 0); break;
			}
			
			handle_green_light = true;			
		}
		if (time_value >= start_red){                          //bắt đầu đèn đỏ
			start_green = start_red + 5000;                    //5s sau thì chuyển sang đèn xanh
			green_light = false;
			handle_green_light = false;
		}
		if (green_light == true)  SDLCommonFunc::ApplySurface(green_doll, g_screen, 1000, 100);
		if (green_light == false) SDLCommonFunc::ApplySurface(red_doll, g_screen, 1000, 100);

		human.HandleMove();
        human.Show(g_screen);

		if (SDL_Flip(g_screen) == -1) return 0;
	}
	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 0;
}