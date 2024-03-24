#include "BaseObject.h"

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

void keepIn(SDL_Rect &rect) {
	if (rect.x < 0) rect.x = 0;
	if (rect.x > width - rect.w) rect.x = width - rect.w;
	if (rect.y < 0) rect.y = 0;
	if (rect.y > heigh - rect.h) rect.y = heigh - rect.h;
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
	IMG_Quit();
	SDL_Quit();
}