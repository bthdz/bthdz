#pragma once

using namespace std;

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string.h>
#include <vector> 
#include <bits/stdc++.h>

const int fps = 100;
const int width = 900; 
const int heigh = 600;
const int planewidth = 50;
const int planeheigh = 22;
const int bulletwidth = 18;
const int bulletheigh = 11;
const int Eplanewidth = 50;
const int Eplaneheigh = 23;
const float planeSpeed = 2.0f;
const float bulletspeed = 5;

static SDL_Window* window = NULL;  
static SDL_Renderer* screen = NULL;
static SDL_Texture* bground = NULL;
static SDL_Texture* plane = NULL;
static SDL_Texture* bulletTexture = NULL;
static SDL_Texture* EbulletTexture = NULL;
static SDL_Texture* Exit = NULL;
static SDL_Texture* start = NULL;
static SDL_Texture* scoreTexture = NULL;

static SDL_Rect rectBG = { 0, 0, width, heigh };
static SDL_Rect rectplane = { 100, heigh/2 - 50, planewidth, planeheigh};
static SDL_Rect exit_ = { width / 2 - 125, 435, 250, 60 };
static SDL_Rect start_ = { width / 2 - 125 , 110, 250, 60 };
static SDL_Rect score_ = { width / 2 - 125 , 270, 250, 60 };
static SDL_Event e;

const int Color_Key_R = 167;
const int Color_Key_G = 175;
const int Color_Key_B = 180;

static float time2 = 0;
static int time_ = 200;
const int Render_Draw_Color = 255;
static SDL_Color textColor = { 255, 150, 0, 255 };
static int score = 0;
static int highScore;

static Mix_Chunk* soundEffect;
static Mix_Chunk* soundEffect1;

static TTF_Font* font;


struct Bullet {
    int x, y;
    int speed;
    Bullet(int startX, int startY, int bulletSpeed) : x(startX), y(startY), speed(bulletSpeed) {}
};

static vector <string> enemyTexture;
static vector<Bullet> bullets;
static bool running = true;
static bool play = false;
static bool scoreCheck = false;