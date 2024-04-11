#include "Common_Function.h"
#include "Mainobject.h"
#include "Light.h"
#include "Text.h"

bool Init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); //định dạng màn hình
	if (g_screen == NULL) return false;

	//Khởi tạo audio
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;
	song1600 = Mix_LoadWAV("song1600.wav");
	song2000 = Mix_LoadWAV("song2000.wav");
	song2500 = Mix_LoadWAV("song2500.wav");
	song3000 = Mix_LoadWAV("song3000.wav");
	look_sound = Mix_LoadWAV("look_sound.wav");
	if (song1600 == NULL || song2000 == NULL || song2500 == NULL || song3000 == NULL || look_sound == NULL) return false;

	//Khởi tạo text
	if (TTF_Init() == -1) return false;
	g_font_text_1 = TTF_OpenFont("ZakirahsBold.TTF", 20); //định dạng font chữ và cỡ chữ
	g_font_text_2 = TTF_OpenFont("OpenSans-ExtraBold.TTF", 40);
	g_font_text_3 = TTF_OpenFont("OpenSans-ExtraBold.TTF", 50);
	g_font_text_4 = TTF_OpenFont("OpenSans-ExtraBold.TTF", 25);
	g_font_text_5 = TTF_OpenFont("OpenSans-ExtraBold.TTF", 32);

	if (g_font_text_1 == NULL || g_font_text_2 == NULL || g_font_text_3 == NULL || g_font_text_4 == NULL || g_font_text_5 == NULL ) return false;

	return true;
}

int main(int arc, char*argv[]){
	
	if (Init() == false) return 0;
	
	g_bkground = SDLCommonFunc::LoadImage("p.background.png"); if (g_bkground == NULL) return 0;
	g_cloud    = SDLCommonFunc::LoadImage("p.cloud.png"); if (g_cloud == NULL) return 0; 
	double cloud_movement = 0;
	green_doll = SDLCommonFunc::LoadImage("p.green_doll.png"); if (green_doll == NULL) return 0;
	red_doll   = SDLCommonFunc::LoadImage("p.red_doll.png"); if (red_doll == NULL) return 0;

	bool in_menu = true, through_menu = false;
	bool in_home = false, in_shop = false, in_game = false, in_last_stand = false, in_instructions = false, through_home = false; //gán bằng gì không quan trọng


	while(in_menu){
		if (through_menu == false){
		int menu_number = SDLCommonFunc::ShowMenu(g_screen, g_font_text_2, g_font_text_3);
		switch (menu_number){
		case 0: through_menu = true; in_home = true; through_home = false; break;
		default: through_menu = false; in_menu = false; break;
		}//kết thúc switch
		}//kết thúc if

		if (through_menu == true){

		while(in_home){
			if (through_home == false){
			int home_number = SDLCommonFunc::ShowHome(g_screen, g_font_text_5, g_font_text_4);
			switch(home_number){
			case -1: through_home = false; in_home = false; in_menu = false; break;
			case 0: through_home = false; in_home = false; in_menu = true; through_menu = false; break;
			case 1: break;
			case 2: through_home = true; in_shop = false; in_instructions = false; in_game = true; break;
			case 3: break;
			case 4: break;
			}//kết thúc switch
			}//kết thúc if
			if (through_home == true){
				while(in_shop){
					//To do
				}//Kết thúc while(in_shop)

				while(in_instructions){
					//To do
				}//Kết thúc while(in_instructions)

				while(in_game){
//Bắt đầu chơi

    Uint32 time_value;
	Uint32 game_start_time = SDL_GetTicks()+1000;   

	MainObject human;
	human.SetRect(0, 250);
	human.SetPicture("man", 8);
	
	bool green_light = true; 
	Uint32 start_green = game_start_time, start_red = -1; 

	Uint32 green_light_time;         //mili giây
	Uint32 game_duration = 45;       //thời gian cho phép (giây)
	bool handle_green_light = false; //đèn xanh đã được xử lí chưa?

	Text time;
	time.SetColor(Text::RED_TEXT);

	while (in_game){
		time_value = SDL_GetTicks();
		while (SDL_PollEvent(&g_event)){
			if (g_event.type == SDL_QUIT){
				in_game = false; in_last_stand = false; in_home = false; in_menu = false;
				break;}
			human.HandleInputAction(g_event);
		}
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);

		//cloud_movement
		cloud_movement -= 0.25;
		SDLCommonFunc::ApplySurface(g_cloud, g_screen, cloud_movement, 0);
		SDLCommonFunc::ApplySurface(g_cloud, g_screen, SCREEN_WIDTH + cloud_movement, 0);
		if (cloud_movement <= -SCREEN_WIDTH) cloud_movement = 0;

		if (!handle_green_light && time_value >= start_green){ //bắt đầu đèn xanh
			green_light_time = RandomNumber()*1000;
			start_red = start_green + green_light_time;        //cài đặt thời gian đèn đỏ tiếp theo
			green_light = true;
			handle_green_light = true;	

			switch(green_light_time){
			case 1600: Mix_PlayChannel(-1, song1600, 0); break;
			case 2000: Mix_PlayChannel(-1, song2000, 0); break;
			case 2500: Mix_PlayChannel(-1, song2500, 0); break;
			case 3000: Mix_PlayChannel(-1, song3000, 0); break;
			}		
		}
		if (handle_green_light && time_value >= start_red){    //bắt đầu đèn đỏ
			start_green = start_red + 5500;                    //6s sau thì chuyển sang đèn xanh
			green_light = false;
			handle_green_light = false;
			human.SetLastPosition();

			Mix_PlayChannel(-1, look_sound, 0);
		}

		if (green_light == true)  SDLCommonFunc::ApplySurface(green_doll, g_screen, 1000, 100);
		if (green_light == false) SDLCommonFunc::ApplySurface(red_doll, g_screen, 1000, 100);

		human.HandleMove();
		human.ShowMainObject(g_screen);

		//hiển thị Time Remaining
		int check_time_remaining = game_duration-(time_value/1000-game_start_time/1000);
		if (check_time_remaining >=0 && check_time_remaining <= game_duration){
		std::string time_remaining = std::to_string(check_time_remaining);
		std::string time_heading("Time Remaining: ");
		time_heading += time_remaining;
		time.SetText(time_heading);
		time.CreateGameText(g_font_text_1, g_screen);
		}

		bool win = false, lose = false;
		if (human.GetRect().x < 940 && check_time_remaining < 0)
			lose = true;
		if (human.GetRect().x >= 940 && check_time_remaining >= 0)
			win = true;
		if ((human.GetRect().x != human.GetLastPosition().x || human.GetRect().y != human.GetLastPosition().y) 
			&& green_light == false)
			lose = true;

		if (win){

		}//kết thúc if(win)
		if (lose){
			//
		}
		
		if (SDL_Flip(g_screen) == -1) return 0;
	}





//Kết thúc chơi
				}
				while(in_last_stand){
					//To do
				}//kết thúc while(in_last_stand)

			}//kết thúc if (through_home == true)

		}//kết thúc while(in_home)

		}//kết thúc if (through_menu == true)
	}//kết thúc while(in_menu)



	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 0;
}