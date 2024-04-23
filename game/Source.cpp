#include "Common_Function.h"
#include "Mainobject.h"
#include "Light.h"
#include "Text.h"
#include "Follower.h"
#include "AutoPlayer.h"

bool Init(){
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE); //định dạng màn hình
	if (g_screen == NULL) return false;

	//Khởi tạo audio
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;

	look_sound = Mix_LoadWAV("look_sound_new.wav");
	shot_sound = Mix_LoadWAV("pistol-shot.wav");
	walking_sound = Mix_LoadWAV("walking-on-floor.wav");

	if (look_sound == NULL || shot_sound == NULL || walking_sound == NULL) 
	return false;

	//Khởi tạo text
	if (TTF_Init() == -1) return false;
	g_font_text_1 = TTF_OpenFont("ZakirahsBold.TTF", 20); //định dạng font chữ và cỡ chữ
	g_font_text_2 = TTF_OpenFont("OpenSans-ExtraBold.TTF", 40);
	g_font_text_3 = TTF_OpenFont("OpenSans-ExtraBold.TTF", 50);
	g_font_text_4 = TTF_OpenFont("OpenSans-ExtraBold.TTF", 25);
	g_font_text_5 = TTF_OpenFont("OpenSans-ExtraBold.TTF", 32);
	g_font_text_7 = TTF_OpenFont("OpenSans-ExtraBold.TTF", 15);

	if (g_font_text_1 == NULL || g_font_text_2 == NULL || g_font_text_3 == NULL || g_font_text_4 == NULL || g_font_text_5 == NULL
		|| g_font_text_7 == NULL) 
		return false;

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
	int total_coins = 25;
	int current_level = 1; 	int price_array[4] = {0, 20, 25, 30};

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
			case 1: through_home = true; in_shop = true; break;
			case 2: through_home = true; in_shop = false; in_instructions = false; in_game = true; break;
			case 3: break;
			case 4: through_home = true; in_shop = false; in_instructions = false; in_game = false; in_last_stand = true; break;
			}//kết thúc switch
			}//kết thúc if
			if (through_home == true){
				while(in_shop){
					int shop_number = SDLCommonFunc::ShowShop(current_level, total_coins, g_screen, g_font_text_4, g_font_text_5);
					switch(shop_number){
					case -1: return 0;
					case 0: in_shop = false; in_instructions = false; in_game = false; in_last_stand = false; in_home = true; through_home = false; break;
					case 9: in_shop = true; break;     //Bấm buy nhưng khi xác nhận thì bấm no hoặc mua xong
					}
				}//Kết thúc while(in_shop)

				while(in_instructions){
					//To do
				}//Kết thúc while(in_instructions)

				while(in_game){
//Bắt đầu chơi
	if (current_level == 4){
		int number_explore_last_stand = SDLCommonFunc::ShowExploreLastStand(g_screen, g_font_text_4);
		switch(number_explore_last_stand){
		case 0: in_game = false; in_last_stand = false; in_home = true; through_home = false; break;
		default: return 0;
		}
		break;
	}
	if (total_coins >= price_array[current_level]){
		int need_to_upgrade_number = SDLCommonFunc::ShowNeedToUpgrade(g_screen, g_font_text_4);
		switch (need_to_upgrade_number){
		case -1: return 0;
		case 0: in_game = false; in_last_stand = false; in_home = true; through_home = false; break;
		case 1: in_game = false; in_last_stand = false; in_home = true; through_home = true; in_shop = true; break;
		default: return 0;
		}
	}

    Uint32 time_value;
	Uint32 game_start_time = SDL_GetTicks()+500; 

	MainObject human;
	human.SetFullRect(0, 250, 120, 180);
	human.SetSpeed(1);

	std::string clothes_type;
	int number_of_frames;
	DetermineClothesTypeAndFrames(current_level, clothes_type, number_of_frames);

	human.SetPicture(clothes_type, number_of_frames);
	g_die = SDLCommonFunc::LoadImage(clothes_type + "_die.png"); if (g_die == NULL) return 0;
	
	Follower guard_1;
	guard_1.SetFullRect(-69, SCREEN_HEIGHT, 69, 110);
	Follower guard_2;
	guard_2.SetFullRect(-69, 200, 69, 110);


	
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
		if (current_level >= 2)
			guard_1.MoveFollower(human.GetRect(), green_light);
		if (current_level == 3)
			guard_2.MoveFollower(human.GetRect(), green_light);

		DisplayObjectsBasedOnLevel(current_level, human, guard_1, guard_2, g_screen);

		//hiển thị Time Remaining
		int check_time_remaining = game_duration-(time_value/1000-game_start_time/1000);
		TimeRemaining(game_duration, check_time_remaining, g_screen, g_font_text_1);
		
		bool win = false, lose = false; int used_time = 0; Uint32 time_die, time_die_check_1, time_die_check_2;

		bool check_collision = false;
		CheckCollisionBasedOnLevel(check_collision, current_level, guard_1, guard_2, human);

		if ((human.GetRect().x < 940 && check_time_remaining < 0)
		|| ((human.GetRect().x != human.GetLastPosition().x || human.GetRect().y != human.GetLastPosition().y) && green_light == false)
		|| check_collision){
			lose = true;
			Mix_PlayChannel(-1, shot_sound, 0); 
			time_die = SDL_GetTicks();
		}
		if (human.GetRect().x >= 940 && check_time_remaining >= 0  && green_light == true){
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
				ShowFollowersBasedOnLevel(current_level, guard_1, guard_2, g_screen);
				
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
				ShowFollowersBasedOnLevel(current_level, guard_1, guard_2, g_screen);

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
//Bắt đầu chơi
	if (current_level < 4){
		//To do
	}
    Uint32 time_value;
	Uint32 game_start_time = SDL_GetTicks()+500; 
	bool green_light = true; 
	Uint32 start_green = game_start_time, start_red = -1; 
	Uint32 red_light_time = 5500;         //mili giây
	Uint32 game_duration = 45;       //thời gian cho phép (giây)
	bool handle_green_light = false; //đèn xanh đã được xử lí chưa?
	double cloud_movement = 0;

	const int numb_autoplayers = 15;
	AutoPlayer auto_player[numb_autoplayers];
	SetRectForArrayOfAutoPlayers(auto_player, numb_autoplayers);

	Text player_name[numb_autoplayers];
	for (int i = 0; i < numb_autoplayers; i++){
		player_name[i].SetRect(auto_player[i].GetRect().x, auto_player[i].GetRect().y);
		player_name[i].SetColor(Text::GREEN_TEXT);
		player_name[i].SetText("Player " + std::to_string(i+1));
	}

	int numb_guards_alive = numb_autoplayers;
	int previous_numb_guards_alive = numb_autoplayers;
	Text numb_guards_alive_text;
	numb_guards_alive_text.SetRect(100, 40);
	numb_guards_alive_text.SetColor(Text::RED_TEXT);
	
	bool any_guard_dead = false; 
	bool any_guard_win = false;
	int red_light_count = 3; //số lần người chơi bật đèn đỏ

	Text red_light_count_text;
	red_light_count_text.SetRect(100, 70);
	red_light_count_text.SetColor(Text::RED_TEXT);

	int channel = Mix_PlayChannel(-1, walking_sound, 0); 

	while (in_last_stand){

		while (SDL_PollEvent(&g_event)){
			if (g_event.type == SDL_QUIT)
				return 0;
			if (green_light == true && g_event.key.keysym.sym == SDLK_SPACE && red_light_count > 0 ){ //bắt đầu đèn đỏ
				Mix_HaltChannel(channel);
				red_light_count -= 1;
				green_light = false;
				start_green = SDL_GetTicks() + red_light_time;
				start_red = SDL_GetTicks();
				Mix_PlayChannel(-1, look_sound, 0);
				handle_green_light = false;
				for (int i = 0; i < numb_autoplayers; i++){
					auto_player[i].SetLastPosition();
				}
			}
		}
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, 0, 0);
		//cloud_movement
		CloudMovement(cloud_movement, g_cloud, g_screen);
		time_value = SDL_GetTicks();
		
		if (!green_light && !handle_green_light && time_value - start_red >= red_light_time){  //bắt đầu đèn xanh
            green_light = true; 
            handle_green_light = true; 
			any_guard_dead = false;
			if (previous_numb_guards_alive > 0)
				channel = Mix_PlayChannel(-1, walking_sound, 0);
        }
		ShowDoll(green_light, green_doll, red_doll, g_screen);

		HandleAutoPlayer(auto_player, player_name, numb_autoplayers, any_guard_dead, g_screen, g_font_text_7);
	
		//hiển thị Time Remaining
		int check_time_remaining = game_duration-(time_value/1000-game_start_time/1000);
		TimeRemaining(game_duration, check_time_remaining, g_screen, g_font_text_1);

		numb_guards_alive = 0;
		for (int i = 0; i < numb_autoplayers; i++){
			//Check alive
			if (auto_player[i].GetAliveOrNot() == true && green_light == false && auto_player[i].GetRect().x != auto_player[i].GetLastPosition().x){ //y khong thay doi
				auto_player[i].SetNotAlive();
				Mix_PlayChannel(-1, shot_sound, 0); 
			}
			//How many guards alive
			if (auto_player[i].GetAliveOrNot() == true)
				numb_guards_alive++;

			//check any_guard_win
			if (auto_player[i].GetRect().x >= 950 && check_time_remaining >= 0  && green_light == true){
				any_guard_win = true;
			}
		}
		if (numb_guards_alive < previous_numb_guards_alive && any_guard_dead == false){
			any_guard_dead = true;
		}

		numb_guards_alive_text.SetText("Guards alive: " + std::to_string(numb_guards_alive));
		numb_guards_alive_text.CreateGameText(g_font_text_1, g_screen);

		red_light_count_text.SetText("Times to turn the red light: " + std::to_string(red_light_count));
		red_light_count_text.CreateGameText(g_font_text_1, g_screen);

		bool win = false, lose = false;

		//if ((numb_guards_alive == 0 && check_time_remaining >= 0 && check_time_remaining <= game_duration)
		//	|| (numb_guards_alive > 0 && check_time_remaining < 0 ) ){
		//	win = true;
		//}
		if (CheckWin(numb_guards_alive, check_time_remaining, game_duration)){
			win = true;
		}
		if (any_guard_win){
			lose = true;
		}

		if (lose){
			Mix_HaltChannel(channel);
			int die_number = SDLCommonFunc::ShowDie(g_screen, g_font_text_4);
			switch(die_number){
			case 0: in_last_stand = false; in_home = true; through_home = false; break;
			default: return 0;		
			}
		}
		if (win){
			//To do
		}


 
		previous_numb_guards_alive = numb_guards_alive;
		if (SDL_Flip(g_screen) == -1) return 0;
	}





//Kết thúc chơi
				}//kết thúc while(in_last_stand)

			}//kết thúc if (through_home == true)

		}//kết thúc while(in_home)

		}//kết thúc if (through_menu == true)
	}//kết thúc while(in_menu)



	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 0;
}