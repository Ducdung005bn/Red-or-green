#include "Instructions.h"

const int IMAGE_WIDTH = 1075;
const int IMAGE_HEIGHT = 1032; 


int ShowInstructions(SDL_Surface* des, TTF_Font* font){
    SDL_Surface* gImageSurface = NULL;
    gImageSurface = SDLCommonFunc::LoadImage("instructions.png");
    if (gImageSurface == NULL) return -1;

    SDL_Surface* g_white_background = NULL;
    g_white_background = SDLCommonFunc::LoadImage("white_background.png");
    if (g_white_background == NULL) return -1;
	SDLCommonFunc::ApplySurface(g_white_background, des, 0, 0);

    SDL_Event e;

    int offsetY = 40;

    // Thiết lập biến để theo dõi trạng thái của phím
    bool isKeyUpPressed = false;
    bool isKeyDownPressed = false;

	SDL_Rect item_position;
	item_position.x = 10 ; item_position.y = 8 ; item_position.w = 86 ; item_position.h = 30 ;

	Text text_return;
	text_return.SetText("Return");
	text_return.SetColor(Text::NAVY_TEXT);
	text_return.SetRect(item_position.x, item_position.y);

	bool selected = false;
	int mouse_x = 0, mouse_y = 0;

    while (true) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                return -1;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        isKeyUpPressed = true;
                        break;
                    case SDLK_DOWN:
                        isKeyDownPressed = true;
                        break;
                    default:
                        break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        isKeyUpPressed = false;
                        break;
                    case SDLK_DOWN:
                        isKeyDownPressed = false;
                        break;
                    default:
                        break;
                }
            } else if (e.type == SDL_MOUSEMOTION){
				if (SDLCommonFunc::MouseCheck(e.motion.x, e.motion.y, item_position)){
							if (selected == false){
								selected = true;
								text_return.SetColor(Text::RED_TEXT);
							}
						}
						else{
							if (selected == true){
								selected = false;
								text_return.SetColor(Text::NAVY_TEXT);
							}
						}
			} else if (e.type == SDL_MOUSEBUTTONDOWN){
				if (SDLCommonFunc::MouseCheck(e.button.x, e.button.y, item_position))
						 return 0;
			}
        }

        // Di chuyển bức ảnh khi nhấn giữ phím
        if (isKeyUpPressed && offsetY < 40) {
            offsetY += 5;
        }
        if (isKeyDownPressed && offsetY > SCREEN_HEIGHT - IMAGE_HEIGHT + 40) {
            offsetY -= 5;
        }

        SDL_Rect destRect = {12, offsetY};
        SDLCommonFunc::ApplySurface(gImageSurface, des, destRect.x, destRect.y);
		text_return.CreateGameText(font, des);
        SDL_Flip(des);
    }
}
