#pragma once

#include "function.h"


SDL_Texture* LoadImage(string path, SDL_Renderer* screen);
void Render(SDL_Texture* texture, SDL_Renderer* screen, SDL_Rect rect);
void cleanup();
void scrollBackground(SDL_Texture* background, SDL_Renderer* renderer, int& backgroundOffsetX, int scrollSpeed);
struct skill {
	bool skill1 = false;
	bool skill2 = false;
	bool skill3 = false;
	float timeSkill1 = 0;
	float timeSkill2 = 0;
	float timeSkill3 = 0;
	Lightning lightning;
	void skillTime();
};
static skill Skills;


