#pragma once

#include "function.h"

SDL_Texture* LoadImage(string path, SDL_Renderer* screen);
void Render(SDL_Texture* texture, SDL_Renderer* screen, SDL_Rect rect);
void cleanup();
void keepIn(SDL_Rect &rect);