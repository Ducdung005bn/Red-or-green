﻿#include "User_Interface.h"

bool MouseCheck(int mouse_x, int mouse_y, SDL_Rect input){
	if (mouse_x >= input.x
	 && mouse_y >= input.y
	 && mouse_y <= input.y + input.h
	 && mouse_x <= input.x + input.w)
	 return true;
	return false;
}

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font1, TTF_Font* font2){ //trả chỉ số chọn item

	g_poster = LoadImage("poster.png"); if (g_poster == NULL) return 1; //1 là exit
	
	const int menu_item_number = 2;
	SDL_Rect item_position[menu_item_number];
	item_position[0].x = 120; item_position[0].y = 100; item_position[0].w = 101 ;item_position[0].h = 47; 
	item_position[1].x = 900; item_position[1].y = 100; item_position[1].w = 87 ;item_position[1].h = 44; 

	Text text_menu[2];
	text_menu[0].SetText("PLAY");
	text_menu[0].SetColor(Text::BLACK_TEXT);
	text_menu[0].SetRect(item_position[0].x, item_position[0].y);

	text_menu[1].SetText("EXIT");
	text_menu[1].SetColor(Text::BLACK_TEXT);
	text_menu[1].SetRect(item_position[1].x, item_position[1].y);

	static TTF_Font* current_font[2];
	current_font[0] = font1; current_font[1] = font1;

	bool selected[menu_item_number] = {0};

	int mouse_x = 0, mouse_y = 0;

	SDL_Event m_event;
	while(true){
		SDLCommonFunc::ApplySurface(g_poster, des, 0, 0);

		for (int i = 0; i < menu_item_number; i++){
			text_menu[i].CreateGameText(current_font[i], des);
		}
		while (SDL_PollEvent(&m_event)){
			switch(m_event.type){
			case SDL_QUIT: return 1; //1 là exit
			case SDL_MOUSEMOTION:
				{
					
					for (int i = 0; i < menu_item_number; i++){
						if (MouseCheck(m_event.motion.x, m_event.motion.y, item_position[i])){
							//nhấp chuột qua, chưa chọn (màu đen) thành chọn (màu đỏ). Nếu chọn rồi (màu đỏ) thì giữ nguyên
							if (selected[i] == false) {
								selected[i] = 1;
								text_menu[i].SetColor(Text::RED_TEXT);
								current_font[i] = font2;
							}
						}
						else{
							//chuột không qua, chưa chọn (màu đen) giữ nguyên. Nếu chọn rồi thì thành chưa chọn (màu đen)
							if (selected[i] == true){
								selected[i] = 0;
								text_menu[i].SetColor(Text::BLACK_TEXT);
								current_font[i] = font1;
							}
						}	 
					} //kết thúc vòng for
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
					for (int i = 0; i < menu_item_number; i++){
						if (MouseCheck(m_event.button.x, m_event.button.y, item_position[i]))
						return i;
					} 
					break;
				}
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
					return 1;
			default: break;
			} //kết thúc switch
		} //kết thúc while
		SDL_Flip(des);
	}//kết thúc while
	return 1;
}

int SDLCommonFunc::ShowHome(int total_coins, SDL_Surface* des, TTF_Font* font1, TTF_Font* font2){

	g_home = LoadImage("home.png");
	if (g_home == NULL) return -1;
	const int home_item_number = 5;
	SDL_Rect item_position[home_item_number];
	item_position[0].x = 10 ; item_position[0].y = 8 ; item_position[0].w = 86 ; item_position[0].h = 30 ;
	item_position[1].x = 590 ; item_position[1].y = 59 ; item_position[1].w = 205; item_position[1].h = 55;
	item_position[2].x = 590; item_position[2].y = 129; item_position[2].w = 205; item_position[2].h = 55;
	item_position[3].x = 590; item_position[3].y = 198; item_position[3].w = 205; item_position[3].h = 55;
	item_position[4].x = 590; item_position[4].y = 265; item_position[4].w = 205; item_position[4].h = 55;

	Text text_home[home_item_number];
	text_home[0].SetText("Return");
	text_home[1].SetText("Shop");
	text_home[2].SetText("Start game");
	text_home[3].SetText("Instructions");
	text_home[4].SetText("Last stand");

	for (int i = 0; i < home_item_number; i++){
		text_home[i].SetColor(Text::BLACK_TEXT);
		text_home[i].SetRect(item_position[i].x, item_position[i].y);
	}

	Text text_coins;
	text_coins.SetText(std::to_string(total_coins));
	text_coins.SetColor(Text::YELLOW_TEXT);
	text_coins.SetRect(950, 35);


	bool selected[home_item_number] = {0};
	int current_home_picture = 0, last_home_picture = 0;
	int mouse_x = 0, mouse_y = 0;
	SDL_Event m_event;

	while(true){
		if (current_home_picture != last_home_picture){
		switch(current_home_picture){
		case 0: g_home = LoadImage("Home.png"); break;
		case 1: g_home = LoadImage("Home1.png"); break;
		case 2: g_home = LoadImage("Home2.png"); break;
		case 3: g_home = LoadImage("Home3.png"); break;
		case 4: g_home = LoadImage("Home4.png"); break;
		}
		if (g_home == NULL) return -1;
		}
		
		SDLCommonFunc::ApplySurface(g_home, des, 0, 0);
		for (int i = 1; i < home_item_number; i++){
			text_home[i].CreateGameText(font1, des);
		}
			text_home[0].CreateGameText(font2, des);

		text_coins.CreateGameText(font1, des);

		last_home_picture = current_home_picture;

		while (SDL_PollEvent(&m_event)){
			switch(m_event.type){
			case SDL_QUIT: return -1;
			case SDL_MOUSEMOTION:
				{
					mouse_x = m_event.motion.x;
					mouse_y = m_event.motion.y;
					for (int i = 0; i < home_item_number; i++){
						if (mouse_x >= item_position[i].x - 62 
						 && mouse_y >= item_position[i].y 
						 && mouse_y <= item_position[i].y + item_position[i].h
						 && mouse_x <= item_position[i].x + item_position[i].w)
						{
							if (selected[i] == false){
								selected[i] = true;
								text_home[i].SetColor(Text::RED_TEXT);
								if (i != 0) current_home_picture = i;
							}
						}
						else{
							if (selected[i] == true){
								selected[i] = false;
								text_home[i].SetColor(Text::BLACK_TEXT);
								if (i != 0) current_home_picture = 0;
							}
						}
					}
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
                        for (int i = 0; i < home_item_number; i++){
						if (MouseCheck(m_event.button.x, m_event.button.y, item_position[i]))
						 return i;
						}
					break;
				}
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
					return -1;
			default: break;
			}
		}
		SDL_Flip(des);
	}
	return -1;
}

int SDLCommonFunc::ShowWin(int this_round_coins, int used_time, SDL_Surface* des, TTF_Font* font){

	//cái HOW? không bấm được. Chuột trong vùng thì hiện.

	g_win = LoadImage("win_picture.png");
	g_how = LoadImage("how_to_play.png");

	if (g_win == NULL || g_how == NULL) return -1;
	const int win_item_number = 3;
	SDL_Rect item_position[win_item_number];
	item_position[0].x = 748 ; item_position[0].y = 165 ; item_position[0].w = 86 ; item_position[0].h = 30 ;
	item_position[1].x = 365 ; item_position[1].y = 435 ; item_position[1].w = 44; item_position[1].h = 30;
	item_position[2].x = 479; item_position[2].y = 435; item_position[2].w = 70; item_position[2].h = 30;

	Text text_win[win_item_number];
	text_win[0].SetText("Return");
	text_win[1].SetText("Yes");
	text_win[2].SetText("How?");

	Text text_time;
	text_time.SetText(std::to_string(used_time));
	text_time.SetColor(Text::RED_TEXT);
	text_time.SetRect(513, 194);

	Text text_coins;
	if (this_round_coins == 0)
		text_coins.SetText("no  coins");
	else if (this_round_coins == 1)
		text_coins.SetText(std::to_string(this_round_coins) + "    coin");
	else
	text_coins.SetText(std::to_string(this_round_coins) + "  coins");

	text_coins.SetColor(Text::RED_TEXT);
	text_coins.SetRect(513, 239);

	for (int i = 0; i < win_item_number; i++){
		text_win[i].SetColor(Text::NAVY_TEXT);
		text_win[i].SetRect(item_position[i].x, item_position[i].y);
	}

	bool selected[win_item_number] = {0};
	int mouse_x = 0, mouse_y = 0;
	SDL_Event m_event;


	while(true){

		SDLCommonFunc::ApplySurface(g_win, des, 233, 119);

		for (int i = 0; i < win_item_number; i++){
			text_win[i].CreateGameText(font, des);
		}

		text_time.CreateGameText(font, des);
		text_coins.CreateGameText(font, des);
		
		if (selected[2] == true)
		SDLCommonFunc::ApplySurface(g_how, des, 300, 200);


		while (SDL_PollEvent(&m_event)){

			switch(m_event.type){
			case SDL_QUIT: return -1;
			case SDL_MOUSEMOTION:
				{
					for (int i = 0; i < win_item_number; i++){
						if (MouseCheck(m_event.motion.x, m_event.motion.y, item_position[i])){
							if (selected[i] == false){
								selected[i] = true;
								text_win[i].SetColor(Text::YELLOW_TEXT);

							}
						}
						else{
							if (selected[i] == true){
								selected[i] = false;
								text_win[i].SetColor(Text::NAVY_TEXT);
							}
						}
					}
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
                        for (int i = 0; i < win_item_number-1 ; i++){ //bấm chuột chỉ nhận return (0) và yes (1). 
						if (MouseCheck(m_event.button.x, m_event.button.y, item_position[i]))
						 return i;
						}
					break;
				}
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
					return -1;
			default: break;
			}


		}
		SDL_Flip(des);
	}
	return -1;
}
int SDLCommonFunc::ShowDie(SDL_Surface* des, TTF_Font* font){
	g_die_announcement = SDLCommonFunc::LoadImageW("die_announcement.png");
	if (g_die_announcement == NULL) return -1;
	Text text_return;
	text_return.SetColor(Text::RED_TEXT);
	text_return.SetText("Return");
	SDL_Rect return_position; return_position.x = 512; return_position.y = 469; return_position.w = 86; return_position.h = 30;
	text_return.SetRect(return_position.x, return_position.y);
	bool selected = 0;
	int mouse_x = 0, mouse_y = 0;
	SDL_Event m_event;
	while(true){

		SDLCommonFunc::ApplySurface(g_die_announcement, des, 320, 90);
		text_return.CreateGameText(font, des);
		
		while (SDL_PollEvent(&m_event)){

			switch(m_event.type){
			case SDL_QUIT: return -1;
			case SDL_MOUSEMOTION:
				{
					if (MouseCheck(m_event.motion.x, m_event.motion.y, return_position)){
							if (selected == false){
								selected = true;
								text_return.SetColor(Text::NAVY_TEXT);
							}
						}
						else{
							if (selected == true){
								selected = false;
								text_return.SetColor(Text::RED_TEXT);
							}
						}
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
						if (MouseCheck(m_event.button.x, m_event.button.y, return_position))
						 return 0;
						
					break;
				}
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
					return -1;
			default: break;
			}


		}
		SDL_Flip(des);
	}
	return -1;
}
int SDLCommonFunc::ShowShop(int& current_level, int& total_coins, SDL_Surface* des, TTF_Font* font1, TTF_Font* font2){
	g_shop = LoadImage("shop.png");
	if (g_shop == NULL) return -1;
	const int home_item_number = 9;
	SDL_Rect item_position[home_item_number];
	int y_all = 524, w_buy = 52, h_buy = 28, w_i = 10, h_i = 30;
	item_position[0].x = 10 ; item_position[0].y = 8 ; item_position[0].w = 86 ; item_position[0].h = 30 ;
	for (int i = 1; i <=4; i++){
		item_position[i].y = y_all;
		item_position[i].w = w_buy;
		item_position[i].h = h_buy;
	}
	for (int i = 5; i <=8; i++){
		item_position[i].y = y_all;
		item_position[i].w = w_i;
		item_position[i].h = h_i;
	}
	item_position[1].x = 145; item_position[5].x = item_position[1].x - 98;
	item_position[2].x = 419; item_position[6].x = item_position[2].x - 98;
	item_position[3].x = 693; item_position[7].x = item_position[3].x - 98;
	item_position[4].x = 967; item_position[8].x = item_position[4].x - 98;

	Text text_home[home_item_number];
	text_home[0].SetText("Return");
	for (int i = 1; i <= 4; i++){
		text_home[i].SetText("BUY");}
	for (int i = 5; i <= 8; i++){
		text_home[i].SetText("i");}

	for (int i = 0; i < home_item_number; i++){
		text_home[i].SetColor(Text::BLACK_TEXT);
		text_home[i].SetRect(item_position[i].x, item_position[i].y);
	}

	Text text_coins;
	text_coins.SetText(std::to_string(total_coins));
	text_coins.SetColor(Text::YELLOW_TEXT);
	text_coins.SetRect(950, 35);

	bool selected[home_item_number] = {0};
	int mouse_x = 0, mouse_y = 0;
	SDL_Event m_event;
	int choose_to_buy = 0; //choose nothing
	int price_array[4] = {100, 200, 300, 400};

	while(true){
				
		SDLCommonFunc::ApplySurface(g_shop, des, 0, 0);
		for (int i = 0; i < home_item_number; i++){
			text_home[i].CreateGameText(font1, des);
		}
		text_coins.CreateGameText(font2, des);

		while (SDL_PollEvent(&m_event)){
			switch(m_event.type){
			case SDL_QUIT: return -1;
			case SDL_MOUSEMOTION:
				{
					for (int i = 0; i < home_item_number; i++){
						if (MouseCheck(m_event.motion.x, m_event.motion.y, item_position[i]))
						{
							if (selected[i] == false){
								selected[i] = true;
								text_home[i].SetColor(Text::RED_TEXT);
							}
						}
						else{
							if (selected[i] == true){
								selected[i] = false;
								text_home[i].SetColor(Text::BLACK_TEXT);
							}
						}
					}
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
						if (MouseCheck(m_event.button.x, m_event.button.y, item_position[0]))
						return 0;
						for (int i = 1; i <=4; i++){
						if (MouseCheck(m_event.button.x, m_event.button.y, item_position[i])){
							choose_to_buy = i; //Bấm chọn mua cái thứ 1, 2, 3 hay 4.
						}
						}
					break;
				}
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
					return -1;
			default: break;
			}
		}
		if (choose_to_buy != 0 && choose_to_buy <= current_level){
			Text cannot_buy;
			cannot_buy.SetColor(Text::NAVY_TEXT);
			cannot_buy.SetText("You cannot buy because you already own this.");
			cannot_buy.SetRect(255, 0);
			int start_time = SDL_GetTicks(); // Thời điểm bắt đầu hiển thị text
			while (SDL_GetTicks() - start_time <= 2000) { // Kiểm tra nếu đã qua 2 giây
				SDLCommonFunc::ApplySurface(g_shop, des, 0, 0); // Vẽ lại cửa hàng
				for (int i = 0; i < home_item_number; i++) {
					if (i != choose_to_buy)  // Không hiển thị text cho lựa chọn được chọn
						text_home[i].CreateGameText(font1, des);
				}
                text_coins.CreateGameText(font2, des);
                cannot_buy.CreateGameText(font1, des); // Hiển thị text không thể mua
                SDL_Flip(des); // Cập nhật màn hình
			}
			choose_to_buy = 0;
		}
		if (choose_to_buy != 0 && choose_to_buy != current_level + 1){
			Text cannot_buy;
			cannot_buy.SetColor(Text::NAVY_TEXT);
			cannot_buy.SetText("You cannot buy because you need to buy item " + std::to_string(current_level + 1) + " first.");
			cannot_buy.SetRect(206, 0);
			int start_time = SDL_GetTicks(); 
			while (SDL_GetTicks() - start_time <= 2000) { 
				SDLCommonFunc::ApplySurface(g_shop, des, 0, 0); 
				for (int i = 0; i < home_item_number; i++) {
					if (i != choose_to_buy)  
						text_home[i].CreateGameText(font1, des);
				}
                text_coins.CreateGameText(font2, des);
                cannot_buy.CreateGameText(font1, des); 
                SDL_Flip(des); 
			}
			choose_to_buy = 0;
		}
		if (choose_to_buy == current_level + 1){
			if (total_coins < price_array[current_level]){
				Text cannot_buy;
			    cannot_buy.SetColor(Text::NAVY_TEXT);
				int lack = price_array[current_level] - total_coins;
				if (lack == 1)
			    cannot_buy.SetText("You lack " + std::to_string(lack) + " coin for this purchase.");
				else if (lack > 1)
				cannot_buy.SetText("You lack " + std::to_string(lack) + " coins for this purchase.");

			    cannot_buy.SetRect(315, 0);
			    int start_time = SDL_GetTicks(); 
			    while (SDL_GetTicks() - start_time <= 2000){ 
				    SDLCommonFunc::ApplySurface(g_shop, des, 0, 0); 
				    for (int i = 0; i < home_item_number; i++) {
					    if (i != choose_to_buy)  
							text_home[i].CreateGameText(font1, des);
				}
                text_coins.CreateGameText(font2, des);
                cannot_buy.CreateGameText(font1, des); 
                SDL_Flip(des); 
				}
				choose_to_buy = 0;
			}
			else{
				bool yes;
				int number_confirm_purchase = ConfirmPurchase(des, font1, choose_to_buy, price_array[current_level]);
				switch(number_confirm_purchase){
				case -1: return -1;
				case 0: yes = true; break;
				case 1: yes = false; break;
				}
				if (!yes) return 9; //quay về in_shop
				if (yes){
					total_coins -= price_array[current_level];
					current_level += 1;
					return 9; //quay về in_shop
				}
			}
		}
		

		SDL_Flip(des);
	}
	return -1;
}
int SDLCommonFunc::ConfirmPurchase(SDL_Surface* des, TTF_Font* font, int index, int price){ //n=4

	g_confirm_purchase = LoadImage("confirm_purchase.png");
	if (g_confirm_purchase == NULL) return -1;

	const int item_number = 2;
	SDL_Rect item_position[item_number];
	item_position[0].x = 380 ; item_position[0].y = 434 ; item_position[0].w = 47 ; item_position[0].h = 30 ;
	item_position[1].x = 675 ; item_position[1].y = 434 ; item_position[1].w = 44; item_position[1].h = 30;

	Text text[item_number];
	text[0].SetText("YES");
	text[1].SetText("NO");

	for (int i = 0; i < item_number; i++){
		text[i].SetColor(Text::NAVY_TEXT);
		text[i].SetRect(item_position[i].x, item_position[i].y);
	}

	Text type; type.SetColor(Text::RED_TEXT); type.SetRect(420, 287);
	switch(index){
	case 1: type.SetText("casual clothes"); break;
	case 2: type.SetText("blue-collar clothes"); break;
	case 3: type.SetText("white-collar clothes"); break;
	case 4: type.SetText("doll clothes"); break;
	}
	Text price_text; price_text.SetColor(Text::RED_TEXT); price_text.SetRect(535, 333);
	price_text.SetText(std::to_string(price));


	bool selected[item_number] = {0};
	int mouse_x = 0, mouse_y = 0;
	SDL_Event m_event;

	while(true){
		SDLCommonFunc::ApplySurface(g_confirm_purchase, des, 220, 144);
		type.CreateGameText(font, des);
		price_text.CreateGameText(font, des);

		for (int i = 0; i < item_number; i++){
			text[i].CreateGameText(font, des);
		}

		while (SDL_PollEvent(&m_event)){

			switch(m_event.type){
			case SDL_QUIT: return -1;
			case SDL_MOUSEMOTION:
				{
					for (int i = 0; i < item_number; i++){
						if (MouseCheck(m_event.motion.x, m_event.motion.y, item_position[i])){
							if (selected[i] == false){
								selected[i] = true;
								text[i].SetColor(Text::GREEN_TEXT);
							}
						}
						else{
							if (selected[i] == true){
								selected[i] = false;
								text[i].SetColor(Text::NAVY_TEXT);
							}
						}
					}
					break;
				}
			case SDL_MOUSEBUTTONDOWN:
				{
                        for (int i = 0; i < item_number ; i++){ 
						if (MouseCheck(m_event.button.x, m_event.button.y, item_position[i]))
						 return i;
						}
					break;
				}
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
					return -1;
			default: break;
			}
		}
		SDL_Flip(des);
	}
	return -1;
}


