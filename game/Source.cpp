#include "Common_Function.h"
#include "Mainobject.h"
#include "Light.h"
#include "Text.h"
#

bool Init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); //định dạng màn hình
	if (g_screen == NULL) return false;

	//Khởi tạo audio
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;

	look_sound = Mix_LoadWAV("look_sound.wav");
	shot_sound = Mix_LoadWAV("pistol-shot.wav");
	if (look_sound == NULL || shot_sound == NULL) 
	return false;

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
	green_doll = SDLCommonFunc::LoadImage("p.green_doll.png"); if (green_doll == NULL) return 0;
	red_doll   = SDLCommonFunc::LoadImage("p.red_doll.png"); if (red_doll == NULL) return 0;

	bool in_menu = true, through_menu = false;
	bool in_home = false, in_shop = false, in_game = false, in_last_stand = false, in_instructions = false, through_home = false; //gán bằng gì không quan trọng
	bool in_game_of_chance = false;
	int total_coins = 0;

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
			int home_number = SDLCommonFunc::ShowHome(total_coins, g_screen, g_font_text_5, g_font_text_4);
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
	Uint32 game_start_time = SDL_GetTicks()+500;   

	std::string clothes_type = "worker";
	g_die = SDLCommonFunc::LoadImage(clothes_type + "_die.png"); if (g_die == NULL) return 0;
	
	MainObject human;
	human.SetRect(0, 250);
	human.SetPicture(clothes_type, 15);
	
	bool green_light = true; 
	Uint32 start_green = game_start_time, start_red = -1; 
	Uint32 green_light_time;         //mili giây
	double green_light_time_array[4] = {1.5, 1.75, 2.275, 2.85};
	Uint32 game_duration = 45;       //thời gian cho phép (giây)
	bool handle_green_light = false; //đèn xanh đã được xử lí chưa?

	int this_round_coins = 0;
	double cloud_movement = 0;

	
	
	while (in_game){
		while (SDL_PollEvent(&g_event)){
			if (g_event.type == SDL_QUIT){
				in_game = false; in_last_stand = false; in_home = false; in_menu = false;
				break;}
			human.HandleInputAction(g_event);
		}
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);

		//cloud_movement
		CloudMovement(cloud_movement, g_cloud, g_screen);

		time_value = SDL_GetTicks();

		if (!handle_green_light && time_value >= start_green){ //bắt đầu đèn xanh
			green_light_time = RandomNumber(green_light_time_array, 4) *1000;
			start_red = start_green + green_light_time;        //cài đặt thời gian đèn đỏ tiếp theo
			green_light = true;
			handle_green_light = true;	
			PlaySong(green_light_time, green_light_time_array, 4);
		}
		if (handle_green_light && time_value >= start_red){    //bắt đầu đèn đỏ
			start_green = start_red + 5500;                    //6s sau thì chuyển sang đèn xanh
			green_light = false;
			handle_green_light = false;
			human.SetLastPosition();
			Mix_PlayChannel(-1, look_sound, 0);
		}

		ShowDoll(green_light, green_doll, red_doll, g_screen);
		
		human.HandleMove();
		human.ShowMainObject(g_screen);

		//hiển thị Time Remaining
		int check_time_remaining = game_duration-(time_value/1000-game_start_time/1000);
		TimeRemaining(game_duration, check_time_remaining, g_screen, g_font_text_1);
		

		bool win = false, lose = false; int used_time = 0; Uint32 time_die, time_die_check_1, time_die_check_2;
		if ((human.GetRect().x < 940 && check_time_remaining < 0)
		|| ((human.GetRect().x != human.GetLastPosition().x || human.GetRect().y != human.GetLastPosition().y) && green_light == false)){
			lose = true;
			Mix_PlayChannel(-1, shot_sound, 0); 
			time_die = SDL_GetTicks();
		}
		if (human.GetRect().x >= 940 && check_time_remaining >= 0){
			win = true;
			used_time = time_value/1000-game_start_time/1000;
			this_round_coins = 45 - used_time;
		}


		bool through_win = false;
		while (win){
			if (through_win == false){
			SDL_Delay(500); 
			int win_number = SDLCommonFunc::ShowWin(this_round_coins, used_time, g_screen, g_font_text_4);
			switch(win_number){
			case -1: through_win = false; win = false; in_game = false; in_last_stand = false; in_home = false; in_menu = false; break;
			case 0: total_coins += this_round_coins; through_win = false; win = false; in_game = false; in_last_stand = false; in_home = true; through_home = false; break;
			case 1: through_win = true; in_game_of_chance = true; break; 
			}

			}//kết thúc if (through_win == false)


			if (through_win == true){
				while(in_game_of_chance){
					in_game_of_chance = false; win = false; in_game = false; in_last_stand = false; in_home = false; in_menu = false; break;


				}//kết thúc while(in_game_of_chance)

			}//kết thúc if (through_win == true)
		}//kết thúc while(win)
		if (lose){
			while (true){
			time_die_check_1 = SDL_GetTicks();
				SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
				CloudMovement(cloud_movement , g_cloud, g_screen);
				TimeRemaining(game_duration, check_time_remaining, g_screen, g_font_text_1);
				ShowDoll(green_light, green_doll, red_doll, g_screen);
				human.Show(g_screen);
			if (time_die_check_1 - time_die >= 850) //850ms là thời gian từ lúc âm thanh kêu đến lúc bị ngã
				break;
			SDL_Flip(g_screen);
			}//phải update lại hết ảnh không thì đám mây sẽ không di chuyển 
			bool check = true;
			while (check)
			{
				SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
				CloudMovement(cloud_movement , g_cloud, g_screen);
				TimeRemaining(game_duration, check_time_remaining, g_screen, g_font_text_1);
				ShowDoll(green_light, green_doll, red_doll, g_screen);
				SDLCommonFunc::ApplySurface(g_die, g_screen, human.GetRect().x, human.GetRect().y + HEIGHT_MAIN_OBJECT - WIDTH_MAIN_OBJECT);
				time_die_check_2 = SDL_GetTicks();

				if (time_die_check_2 - time_die_check_1 >= 3000){
					int die_number = SDLCommonFunc::ShowDie(g_screen, g_font_text_4);
					switch(die_number){
					case 0: check = false; in_game = false; in_last_stand = false; in_home = true; through_home = false; break;
					default: return 0;		
					}
				}
				SDL_Flip(g_screen);
			}
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