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
				enemies[i].shoot(rectplane);
			}
			else {
				enemies.erase(enemies.begin() + i);
				i--;
			}
		}
		else {
			SDL_Rect rect = { enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h };
			Render(enemies[i].eplane, screen, rect);
			enemies[i].shoot(rectplane);
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
void Menu(SDL_Renderer* screen1, SDL_Texture* start, SDL_Texture* exit, SDL_Texture* scoreTexture) {
	Render(bground, screen1, rectBG);
	Render(start, screen1, start_);
	Render(scoreTexture, screen1, score_);
	Render(Exit, screen1, exit_);
	SDL_RenderPresent(screen1);
}
void renderScore() {
	string scoreStr;
	ifstream in;
	in.open("score.txt");
	if (in.is_open()) {
		in >> highScore;
		in.close();
	}
	if (score > highScore) {
		highScore = score;
		ofstream out;
		out.open("score.txt");
		if (out.is_open()) {
			out << highScore;
			out.close();
		}
		scoreStr = "High score: " + to_string(score);
	}
	else {
		scoreStr = "Score: " + to_string(score);
	}
	string back_to_menu = "Press space to return to the menu";
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
	SDL_Rect dstRect = { width / 2 - 100, heigh / 2 - 50, 200, 50 };
	SDL_RenderCopy(screen, textTexture, NULL, &dstRect);
	SDL_Surface* returnMenu = TTF_RenderText_Solid(font, back_to_menu.c_str(), textColor);
	SDL_Texture* returnMenuTexture = SDL_CreateTextureFromSurface(screen, returnMenu);
	SDL_Rect dstRect1 = { width / 2 - 250, heigh / 2 + 50, 500, 50 };
	SDL_RenderCopy(screen, returnMenuTexture, NULL, &dstRect1);
	SDL_Surface* gameover = TTF_RenderText_Solid(font, "GAME OVER", textColor);
	SDL_Texture* gameoverTexture = SDL_CreateTextureFromSurface(screen, gameover);
	SDL_Rect dstRect2 = { width / 2 - 200, heigh / 2 - 200, 400, 50 };
	SDL_RenderCopy(screen, gameoverTexture, NULL, &dstRect2);
	SDL_RenderPresent(screen);
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(returnMenu);
	SDL_FreeSurface(gameover);
	

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			running = false;
			break;
		}
		else if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_SPACE) {
				SDL_DestroyTexture(textTexture);
				SDL_DestroyTexture(returnMenuTexture);
				SDL_DestroyTexture(gameoverTexture);
				scoreCheck = false;
				score = 0;
				break;
			}
		}
	}
}
void checkCollision(int score, SDL_Renderer* renderer) {
	for (size_t i = 0; i < enemies.size(); i++) {
		if (planeCollision(enemies[i].Ebullets, rectplane, enemies) || planeCollision(enemyBullet, rectplane, enemies)) {
			Mix_PlayChannel(-1, soundEffect1, 0);
			cleanPlay(enemies, bullets, enemyBullet, rectplane, rectBG, time_);
			play = false;
			scoreCheck = true;
			break;
		}
	}
}
void enemyShoot() {
	for (int i = 0; i < enemyBullet.size(); i++) {
		SDL_Rect rect = { enemyBullet[i].x, enemyBullet[i].y, bulletwidth, bulletheigh };
		enemyBullet[i].x -= bulletspeed;
		Render(EbulletTexture, screen, rect);
		if (enemyBullet[i].x <= 0) {
			enemyBullet.erase(enemyBullet.begin() + i);
			if (i >= 1) i--;
		}
	}
}
void currentScore() {
	string scoreStr = "Score: " + to_string(score);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
	SDL_Rect dstRect = { 0, 0, 100, 30 };
	SDL_RenderCopy(screen, textTexture, NULL, &dstRect);
	SDL_RenderPresent(screen);
	SDL_FreeSurface(textSurface);
}
void loadMedia(){
	bground = LoadImage("image/sk2.png", screen);
	plane = LoadImage("image/plane.png", screen);
	bulletTexture = LoadImage("image/bullet3.png", screen);
	EbulletTexture = LoadImage("image/bullet4.png", screen);
	start = LoadImage("image/start.png", screen);
	Exit = LoadImage("image/exit.png", screen);
	scoreTexture = LoadImage("image/score.png", screen);

	soundEffect = Mix_LoadWAV("image/Gun.wav");
	soundEffect1 = Mix_LoadWAV("image/Explore.wav");
	font = TTF_OpenFont("font/arial.ttf", 24);
	
}



int main(int argv, char* argc[]) {
	if (!init()) {
		cout << "loi cua so: " << SDL_GetError();
		return -1;
	}
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
		return -1;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
		return -1;
	}
	loadMedia();
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
		if (play == false && scoreCheck == false) {
			Menu(screen, start, Exit, scoreTexture);
		}
		else if(play == true && scoreCheck == false){
			float time1 = SDL_GetTicks() / 1000;
			time_eplane(time1, time_, time2);
			fps_timer.start();
			Render(bground, screen, rectBG);
			scrollBackground(bground, screen, rectBG.x, 1);
			Render(plane, screen, rectplane);
			// di chuyen may bay
			planemove(rectplane, planeSpeed);
			// dan may bay
			fire();
			// tao may bay dich
			createEnemies();
			//check va cham
			for (size_t i = 0; i < enemies.size(); i++) {
				bulletCollision(bullets, enemies[i].Ebullets);
				bulletCollision(bullets, enemyBullet);
			}
			EplaneCollision(bullets, enemies, enemyBullet, score, soundEffect1);
			// dan da ban cua may bay dich
			enemyShoot();
			// diem hien tai
			currentScore();
			// chech va cham end game
			checkCollision(score, screen);
			// fps
			int real_time = fps_timer.get_ticks();
			int timeframe = 1000 / fps;
			if (real_time < timeframe) {
				int delayTime = timeframe - real_time;
				if (delayTime >= 0) {
					SDL_Delay(delayTime);
				}
			}
			cout << highScore << endl;
		}
		else {
			Render(bground, screen, rectBG);
			renderScore();
		}
	}
	cleanup();
	return 0;
}

