#pragma once

using namespace std;

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string.h>
#include <vector> 


const int width = 1200;
const int heigh = 600;
const int planewidth = 50;
const int planeheigh = 30;
const int bulletwidth = 15;
const int bulletheigh = 10;
const int Eplanewidth = 50;
const int Eplaneheigh = 50;

static SDL_Window* window = NULL;  
static SDL_Renderer* screen = NULL;
static SDL_Texture* bground = NULL;
static SDL_Texture* plane = NULL;
static SDL_Texture* eplane = NULL;
static SDL_Texture* bulletTexture = NULL;

static SDL_Rect rectBG = { 0, 0, width, heigh };
static SDL_Rect rectplane = { 100, heigh/2 - 50, planewidth, planeheigh};
static SDL_Event e;

const int Color_Key_R = 167;
const int Color_Key_G = 175;
const int Color_Key_B = 180;
const float planeSpeed = 2.0f;
const float bulletspeed = 3.5f;

const int Render_Draw_Color = 255;

struct Bullet {
    int x, y;
    int speed;

    Bullet(int startX, int startY, int bulletSpeed) : x(startX), y(startY), speed(bulletSpeed) {}
};
static vector<Bullet> bullets;