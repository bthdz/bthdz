#include "function.h"
#include "BaseObject.h"
#include "motion.h"
#include "enemyplane.h"
#include "collision.h"


bool init() {
	if (TTF_Init() == -1) return false;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
	window = SDL_CreateWindow("ban may bay", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, heigh, SDL_WINDOW_SHOWN);
	if (window == NULL) return false;
	else {
		screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (screen == NULL) {
			return false;
		}
		else {
			SDL_SetRenderDrawColor(screen, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color, Render_Draw_Color);
			int imageflag = IMG_INIT_JPG;
			if (!(IMG_Init(imageflag) && imageflag)) {
				return false;
			}
		}
	}
	return true;
}
void createEplane() {
	if (enemies.size() == 0) {
		Eplane a(Eplanewidth, Eplaneheigh);
		a.createpos();
		a.createspeed();
		string c = a.randomEnemy();
		a.eplane = LoadImage(c, screen);
		enemies.push_back(a);
	}
	else if (enemies[enemies.size() - 1].x < width - time_) {
		Eplane a(Eplanewidth, Eplaneheigh);
		a.createpos();
		a.createspeed();
		string c = a.randomEnemy();
		a.eplane = LoadImage(c, screen);
		if (a.eplane == NULL)
		{
			cout << "loi may bay dich: " << endl;
		}
		enemies.push_back(a);
	}
}
void enemyMotion() {
	for (size_t i = 0; i < enemies.size(); i++) {
		enemies[i].x -= enemies[i].speed;
		if (enemies.size() >= 2 && i == enemies.size() - 1) {
			if (checkpos(enemies[i], enemies)) {
				SDL_Rect rect = { enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h };
				Render(enemies[i].eplane, screen, rect);
				enemies[i].shoot();
			}
			else {
				enemies.erase(enemies.begin() + i);
				i--;
			}
		}
		else {
			SDL_Rect rect = { enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h };
			Render(enemies[i].eplane, screen, rect);
			enemies[i].shoot();
		}
		if (enemies[i].x <= 0) {
			enemies.erase(enemies.begin() + i);
			i--;
		}
	}
}
void createEnemies() {
	createEplane();
	enemyMotion();
}
void fire() {
	for (size_t i = 0; i < bullets.size(); i++) {
		bullets[i].x += bulletspeed;
		SDL_Rect rectbullet = { bullets[i].x,bullets[i].y, bulletwidth, bulletheigh };
		Render(bulletTexture, screen, rectbullet);
		if (bullets[i].x > width) {
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}
void cleanPlay( vector<Eplane>& enemies, vector<Bullet> &Bullets, vector<Bullet>& Ebullets, SDL_Rect &RectPlane, SDL_Rect &rectbg, int &time_) {
	enemies.clear();
	Bullets.clear();
	Ebullets.clear();
	RectPlane = { 100, heigh / 2 - 50, planewidth, planeheigh };
	rectbg = { 0, 0, width, heigh };
	time_ = 200;
}
void checkCollision()  {
	for (size_t i = 0; i < enemies.size(); i++) {
		if (planeCollision(enemies[i].Ebullets, rectplane, enemies) || planeCollision(enemyBullet, rectplane, enemies)) {
			play = false;
			cleanPlay(enemies, bullets, enemyBullet, rectplane, rectBG, time_);
			SDL_RenderClear(screen);
			break;
		}
	}
} 
void Menu(SDL_Renderer* screen1, SDL_Texture* start, SDL_Texture* exit, SDL_Texture* scoreTexture) {
	Render(bground, screen1, rectBG);
	Render(start, screen1, start_);
	Render(scoreTexture, screen1, score_);
	Render(Exit, screen1, exit_);
	SDL_RenderPresent(screen1);
}
void renderScore(int score, TTF_Font* font, SDL_Renderer* renderer) {
	
	string scoreStr = "Score: " + to_string(score);

	
	SDL_Color textColor = { 255, 255, 255, 255 }; 

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
		
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			
			SDL_Rect dstRect = { width/2 - 100, heigh/2 - 50, 200, 50 };

			
			SDL_RenderCopy(renderer, textTexture, NULL, &dstRect);
			SDL_RenderPresent(renderer);
		

}


int main(int argv, char* argc[]) {
	// tao cua so
	if (!init()) {
		cout << "loi cua so: " << SDL_GetError();
		return -1;
	}
	// khoi tao mixer
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		return -1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return -1;
	}

	bground = LoadImage("image/sk2.png", screen);
	plane = LoadImage("image/plane.png", screen);
	start = LoadImage("image/start.png", screen);
	Exit = LoadImage("image/exit.png", screen);
	scoreTexture = LoadImage("image/score.png", screen);
	
	bulletTexture = LoadImage("image/bullet3.png", screen);
	soundEffect = Mix_LoadWAV("image/Gun.wav");
	soundEffect1 = Mix_LoadWAV("image/Explore.wav");
	font = TTF_OpenFont("font/arial.ttf", 50);

	if (bground == NULL) {
		cout << "loi bground: " << SDL_GetError();
		return -1;
	}
	if (plane == NULL) {
		cout << "loi nhan vat: " << SDL_GetError();
		return -1;
	}
	if (bulletTexture == NULL) {
		cout << "loi dan: " << SDL_GetError();
		return -1;
	}
	int c = 0;
	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (play == false) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (x >= start_.x && x <= start_.x + 250 && y >= start_.y && y <= start_.y + 60) {
						play = true;
					}
					else if (x >= exit_.x && x <= exit_.x + 250 && y >= exit_.y && y <= exit_.y + 60) {
						running = false;
					}
				}
				else {
					bullets.push_back(Bullet(rectplane.x + rectplane.w, rectplane.y + rectplane.h / 2 - 5, 1));
					Mix_PlayChannel(-1, soundEffect, 0);
				}
			}
		}
		if (play == false) {
			renderScore(score, font, screen);
			if (SDL_PollEvent(&e)) {
				if (e.type == SDL_KEYDOWN) {
					
						TTF_CloseFont(font);
						Menu(screen, start, Exit, scoreTexture);
					
				}
			}
		}
		else {
			c = 1;
			float time = SDL_GetTicks() / 1000;
			time_eplane(time, time_, time1);
			fps_timer.start();
			// di chuyen may bay
			planemove(rectplane, planeSpeed);
			Render(bground, screen, rectBG);
			scrollBackground(bground, screen, rectBG.x, 1);
			Render(plane, screen, rectplane);
			// dan may bay
			fire();
			// tao may bay dich
			createEnemies();
			// dan da ban cua may bay dich
			for (int i = 0; i < enemyBullet.size(); i++) {
				SDL_Rect rect = { enemyBullet[i].x, enemyBullet[i].y, bulletwidth, bulletheigh };
				enemyBullet[i].x -= bulletspeed;
				Render(bulletTexture, screen, rect);
				if (enemyBullet[i].x <= 0) {
					enemyBullet.erase(enemyBullet.begin() + i);
					i--;
				}
			}
			//check va cham
			for (size_t i = 0; i < enemies.size(); i++) {
				bulletCollision(bullets, enemies[i].Ebullets);
				bulletCollision(bullets, enemyBullet);
			}
			EplaneCollision(bullets, enemies, enemyBullet, score, soundEffect1);
			SDL_RenderPresent(screen);
			// chech va cham
			checkCollision();
			// fps
			int real_time = fps_timer.get_ticks();
			int timeframe = 1000 / fps;
			if (real_time < timeframe) {
				int delayTime = timeframe - real_time;
				if (delayTime >= 0) {
					SDL_Delay(delayTime);
				}
			}
		}
	}
	cleanup();
	return 0;
}

