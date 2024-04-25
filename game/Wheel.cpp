#include "Wheel.h"

// Hàm lấy màu của pixel từ một SDL_Surface tại một tọa độ cụ thể
Uint32 getPixel(SDL_Surface* surface, int x, int y) {
    // Tính toán địa chỉ của pixel trong bộ nhớ
    Uint8* pixelAddress = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;

    // Đọc giá trị màu từ địa chỉ đã tính toán
    switch (surface->format->BytesPerPixel) {
        case 1:
            return *pixelAddress;
        case 2:
            return *(Uint16*)pixelAddress;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return pixelAddress[0] << 16 | pixelAddress[1] << 8 | pixelAddress[2];
            else
                return pixelAddress[0] | pixelAddress[1] << 8 | pixelAddress[2] << 16;
        case 4:
            return *(Uint32*)pixelAddress;
        default:
            return 0; // Trả về màu đen nếu không xác định được định dạng pixel
    }
}

// Hàm đặt màu của một pixel trong một SDL_Surface tại một tọa độ cụ thể
void putPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
    // Tính toán địa chỉ của pixel trong bộ nhớ
    Uint8* pixelAddress = (Uint8*)surface->pixels + y * surface->pitch + x * surface->format->BytesPerPixel;

    // Ghi giá trị màu vào địa chỉ đã tính toán
    switch (surface->format->BytesPerPixel) {
        case 1:
            *pixelAddress = pixel;
            break;
        case 2:
            *(Uint16*)pixelAddress = pixel;
            break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                pixelAddress[0] = (pixel >> 16) & 0xFF;
                pixelAddress[1] = (pixel >> 8) & 0xFF;
                pixelAddress[2] = pixel & 0xFF;
            } else {
                pixelAddress[0] = pixel & 0xFF;
                pixelAddress[1] = (pixel >> 8) & 0xFF;
                pixelAddress[2] = (pixel >> 16) & 0xFF;
            }
            break;
        case 4:
            *(Uint32*)pixelAddress = pixel;
            break;
        default:
            break; // Không làm gì nếu không xác định được định dạng pixel
    }
}

// Hàm quay bức ảnh
SDL_Surface* rotateSurface(SDL_Surface* src, double angle) {
    // Tính toán kích thước mới cho bức ảnh quay
    int newWidth = static_cast<int>(std::abs(src->w * cos(angle)) + std::abs(src->h * sin(angle)));
    int newHeight = static_cast<int>(std::abs(src->w * sin(angle)) + std::abs(src->h * cos(angle)));

    // Tạo một bức ảnh mới có kích thước mới
    SDL_Surface* rotatedSurface = SDL_CreateRGBSurface(0, newWidth, newHeight, src->format->BitsPerPixel,
                                                       src->format->Rmask, src->format->Gmask,
                                                       src->format->Bmask, src->format->Amask);

    // Lặp qua từng pixel trong bức ảnh mới và quay từng pixel trong bức ảnh gốc
    for (int x = 0; x < newWidth; ++x) {
        for (int y = 0; y < newHeight; ++y) {
            // Tính toán tọa độ pixel tương ứng trên bức ảnh gốc
            double srcX = (x - newWidth / 2) * cos(angle) + (y - newHeight / 2) * sin(angle) + src->w / 2;
            double srcY = -(x - newWidth / 2) * sin(angle) + (y - newHeight / 2) * cos(angle) + src->h / 2;

            // Kiểm tra xem tọa độ pixel có nằm trong bức ảnh gốc không
            if (srcX >= 0 && srcX < src->w && srcY >= 0 && srcY < src->h) {
                // Lấy màu của pixel từ bức ảnh gốc
                Uint32 pixel = getPixel(src, srcX, srcY);

                // Đặt màu của pixel vào bức ảnh mới
                putPixel(rotatedSurface, x, y, pixel);
            }
        }
    }

    return rotatedSurface;
}

int calculateSelectedSector(double rotationAngle) {
	// Chuyển góc quay về khoảng [0, 360)
    while (rotationAngle < 0) {
        rotationAngle += 360;
    }
    while (rotationAngle >= 360) {
        rotationAngle -= 360;
    }
    
    // Tính chỉ số sector dựa trên góc quay
    int sectorIndex = static_cast<int>(rotationAngle / 11.2)%12 + 1;
    
    return sectorIndex;
}

int SDLCommonFunc::ShowGameOfChance(int& this_round_coins, SDL_Surface* des, TTF_Font* font){
	
	// Khai báo tâm của bức ảnh
	int centerX = SCREEN_WIDTH / 2;
	int centerY = SCREEN_HEIGHT / 2;
	
	// Góc quay hiện tại
	int angle = 0;

	SDL_Surface* wheel_picture = NULL;
	wheel_picture =  SDLCommonFunc::LoadImage("wheel.png");

	SDL_Surface* pointer_picture = NULL;
	pointer_picture =  SDLCommonFunc::LoadImage("pointer.png");

	SDL_Surface* g_black_background = NULL;
	g_black_background =  SDLCommonFunc::LoadImage("black_background.png");

	if (wheel_picture == NULL || pointer_picture == NULL || g_black_background == NULL)
		return -1;
	
	int ROTATION_SPEED = 1;
	Uint32 DELAY_TIME = 10;

	SDL_Event m_event;
	bool press = false; Uint32 press_time;
	bool stop_rotating = false;
	srand(time(0));
	int random_time;


	Text coins_text;
	coins_text.SetRect(0, 0);
	coins_text.SetColor(Text::YELLOW_TEXT);
	coins_text.SetText("Coins: " + std::to_string(this_round_coins));

	Text press_space;
	press_space.SetRect(280, 0);
	press_space.SetColor(Text::RED_TEXT);
	press_space.SetText("Press the 'Space' button to stop the wheel.");

	bool green = true;
	int selected_sector;
	int previous_selected_sector = calculateSelectedSector(0);

	Mix_HaltChannel(-1);
	spinning_wheel_sound= Mix_LoadWAV("spinning_wheel.wav");
	if (spinning_wheel_sound == NULL) return -1;
	int channel = Mix_PlayChannel(-1, spinning_wheel_sound, 0);


	while (true) {
		if (Mix_Playing(channel) == 0) 
            Mix_PlayChannel(-1, spinning_wheel_sound, 0);

		while (SDL_PollEvent(&m_event)){
			switch(m_event.type){
			case SDL_QUIT: return -1; 
			case SDL_KEYDOWN: {
				if (m_event.key.keysym.sym == SDLK_SPACE){
					press = true;
					press_time = SDL_GetTicks();
					random_time = (rand() % 9 + 1)*1000;
				}
				break;
							  }
			}
		}

		// Xóa màn hình
		SDLCommonFunc::ApplySurface(g_black_background, des, 0, 0);
		// Quay bức ảnh
		SDL_Surface* rotatedImage = rotateSurface(wheel_picture, angle);
		
		// Tính toán vị trí để hiển thị bức ảnh quay trên màn hình
		int imageX = centerX - rotatedImage->w / 2;
		int imageY = centerY - rotatedImage->h / 2;
		
		// Hiển thị bức ảnh quay trên màn hình
		SDLCommonFunc::ApplySurface(rotatedImage, des, imageX, imageY);
		SDLCommonFunc::ApplySurface(pointer_picture, des, 250, 280);
		coins_text.CreateGameText(font, des);
		press_space.CreateGameText(font, des);

		selected_sector = calculateSelectedSector(angle);
		if (selected_sector != previous_selected_sector)
			green = !green;

		if (press && SDL_GetTicks() - press_time >= random_time)
			stop_rotating = true;

		if (stop_rotating){
			Mix_HaltChannel(-1);
			if (green){
				int start_time = SDL_GetTicks();
				Text win; 
				win.SetColor(Text::RED_TEXT);
				win.SetRect(0, 32);
				win.SetText("The number of coins you've earned has increased from " + std::to_string(this_round_coins) + " to " + std::to_string(this_round_coins*2) + ".");
				this_round_coins *= 2;
				while(SDL_GetTicks() - start_time <= 5000){
					SDLCommonFunc::ApplySurface(g_black_background, des, 0, 0);
					SDLCommonFunc::ApplySurface(rotatedImage, des, imageX, imageY);
					SDLCommonFunc::ApplySurface(pointer_picture, des, 250, 280);
					coins_text.SetText("Coins: " + std::to_string(this_round_coins));
					coins_text.CreateGameText(font, des);
					press_space.CreateGameText(font, des);
					win.CreateGameText(font, des);
					SDL_Flip(des);
				}
				return 0; 
			}
			else{
				int start_time = SDL_GetTicks();
				Text lose; 
				lose.SetColor(Text::RED_TEXT);
				lose.SetRect(0, 32);
				lose.SetText("You have lost " + std::to_string(this_round_coins) + " coins.");
				this_round_coins = 0;
				while(SDL_GetTicks() - start_time <= 5000){
					SDLCommonFunc::ApplySurface(g_black_background, des, 0, 0);
					SDLCommonFunc::ApplySurface(rotatedImage, des, imageX, imageY);
					SDLCommonFunc::ApplySurface(pointer_picture, des, 250, 280);
					coins_text.SetText("Coins: " + std::to_string(this_round_coins));
					coins_text.CreateGameText(font, des);
					press_space.CreateGameText(font, des);
					lose.CreateGameText(font, des);
					SDL_Flip(des);
				}
				return 0; 
			}
		}
		

		// Tăng góc quay
		angle += ROTATION_SPEED;
		if (angle >= 135) {
        angle = 0;
		}

		previous_selected_sector = selected_sector;
		
		SDL_Flip(des);
		SDL_FreeSurface(rotatedImage);
		SDL_Delay(DELAY_TIME);
	}

}

