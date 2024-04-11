#include "BaseObject.h"
#include "function.h"
SDL_Texture* LoadImage(string path, SDL_Renderer* screen) {
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_Image = IMG_Load(path.c_str());
	if (load_Image != NULL) {
		SDL_SetColorKey(load_Image, SDL_TRUE, SDL_MapRGB(load_Image->format, Color_Key_R, Color_Key_G, Color_Key_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_Image);
		SDL_FreeSurface(load_Image);
	}
	return new_texture;
}

void Render(SDL_Texture* texture, SDL_Renderer* screen, SDL_Rect rect) {
	SDL_RenderCopy(screen, texture, NULL, &rect);
}

void cleanup() {
	SDL_DestroyTexture(plane);
	plane = NULL;
	SDL_DestroyTexture(bground);
	bground = NULL;
	SDL_DestroyTexture(bulletTexture);
	bulletTexture = NULL;
	SDL_DestroyRenderer(screen);
	screen = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyTexture(start);
	start = NULL;
	SDL_DestroyTexture(Exit);
	Exit = NULL;
	SDL_DestroyTexture(scoreTexture);
	scoreTexture = NULL;
	IMG_Quit();
	SDL_Quit();
}

void scrollBackground(SDL_Texture* background, SDL_Renderer* renderer, int& backgroundOffsetX, int scrollSpeed) {
	
	backgroundOffsetX -= scrollSpeed;

	if (backgroundOffsetX < -width) {
		backgroundOffsetX = 0;
	}

	SDL_Rect srcRect = { 0, 0, width, heigh };
	SDL_Rect destRect = { backgroundOffsetX, 0, width, heigh };
	SDL_RenderCopy(renderer, background, &srcRect, &destRect);

	destRect.x = backgroundOffsetX + width;
	SDL_RenderCopy(renderer, background, &srcRect, &destRect);
}

//void createItems() {
//	int x = rand() % (width - 20);
//	int y = rand() % (heigh - 20);
//
//
//}
