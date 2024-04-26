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
void Eshoot() {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i].shoot(rectplane);
	}
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
void cleanPlay(vector<Eplane>& enemies, vector<Bullet>& Bullets, vector<Bullet>& Ebullets, SDL_Rect& RectPlane, SDL_Rect& rectbg, int& time_) {
	enemies.clear();
	Bullets.clear();
	Ebullets.clear();
	RectPlane = { 100, heigh / 2 - 50, planewidth, planeheigh };
	rectbg = { 0, 0, width, heigh };
	time_ = 200;
	healthRect = { width / 2 - 150, 0, 200, 20 };
	float current_time = SDL_GetTicks() / 1000;
	Skills.timeSkill1 = current_time;
	Skills.timeSkill2 = current_time;
	Skills.timeSkill3 = current_time;
}
void Menu(SDL_Renderer* screen1, SDL_Texture* start, SDL_Texture* exit, SDL_Texture* scoreTexture) {
	Render(bground, screen1, rectBG);
	Render(plane, screen1, { 100, 50, 100, 44 });
	SDL_Texture* plane1 = LoadImage("image/plane2.png", screen1);
	Render(plane1, screen1, { 700, 100, 100, 44 });
	SDL_Texture* plane2 = LoadImage("image/plane3.png", screen1);
	Render(plane2, screen1, { 60, 370, 100, 44 });
	SDL_Texture* plane3 = LoadImage("image/plane1.png", screen1);
	Render(plane3, screen1, { 700, 400, 100, 44 });
	Render(Skills.lightning.lightning5, screen1, { 100, 300, 50, 80 });
	Render(start, screen1, start_);
	Render(scoreTexture, screen1, score_);
	Render(Exit, screen1, exit_);
	SDL_RenderPresent(screen1);
	SDL_DestroyTexture(plane1);
	SDL_DestroyTexture(plane2);
	SDL_DestroyTexture(plane3);
}

int getHighestScore() {
	int highestscore ;
	ifstream inFile;
	inFile.open("score.txt");
	if (inFile.is_open()) {
		inFile >> highestscore;
		inFile.close();
	}
	return highestscore;
}


void renderScore() {
	string scoreStr;
	int highestscore = getHighestScore();
	cout << highestscore << endl;
	if(score <= highestscore) {
		scoreStr = "Score: " + to_string(score);
	}
	else {
		highestscore = score;
		ofstream outFile;
		outFile.open("score.txt");
		if (outFile.is_open()) {
			outFile << highestscore;
			outFile.close();
		}
		scoreStr = "New High Score: " + to_string(score);
	}

	string back_to_menu = "Press space to return to the menu";
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
	SDL_Rect dstRect = { width / 2 - 100, heigh / 2 - 50, 200, 50 };
	SDL_RenderCopy(screen, textTexture, NULL, &dstRect);
	SDL_Surface* returnMenu = TTF_RenderText_Solid(font, back_to_menu.c_str(), textColor);
	SDL_Texture* returnMenuTexture = SDL_CreateTextureFromSurface(screen, returnMenu);
	SDL_Rect dstRect1 = { width / 2 - 250, heigh / 2 + 100, 500, 50 };
	SDL_RenderCopy(screen, returnMenuTexture, NULL, &dstRect1);
	SDL_Surface* gameover = TTF_RenderText_Solid(font, "GAME OVER", textColor);
	SDL_Texture* gameoverTexture = SDL_CreateTextureFromSurface(screen, gameover);
	SDL_Rect dstRect2 = { width / 2 - 200, heigh / 2 - 200, 400, 50 };
	SDL_RenderCopy(screen, gameoverTexture, NULL, &dstRect2);
	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(returnMenu);
	SDL_FreeSurface(gameover);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(returnMenuTexture);
	SDL_DestroyTexture(gameoverTexture);

	SDL_RenderPresent(screen);
}
void checkCollision() {
	for (size_t i = 0; i < enemies.size(); i++) {
		if (planeCollision(enemies[i].Ebullets, rectplane, enemies, score) || planeCollision(enemyBullet, rectplane, enemies, score)) {
			if (healthRect.w > 0) {
				Mix_PlayChannel(-1, healthSound, 0);
				healthRect.w -= 10;
			}
			else {
				Mix_PlayChannel(-1, soundEffect1, 0);
				cleanPlay(enemies, bullets, enemyBullet, rectplane, rectBG, time_);
				play = false;
				scoreCheck = true;
				break;
			}	
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
void loadMedia() {
	bground = LoadImage("image/sk2.png", screen);
	plane = LoadImage("image/plane.png", screen);
	bulletTexture = LoadImage("image/bullet3.png", screen);
	EbulletTexture = LoadImage("image/bullet4.png", screen);
	start = LoadImage("image/start.png", screen);
	Exit = LoadImage("image/exit.png", screen);
	scoreTexture = LoadImage("image/score.png", screen);
	healthTexture = LoadImage("image/health.png", screen);
	hpTexture = LoadImage("image/hp.png", screen);
	Skills.lightning.lightning0 = LoadImage("image/lightning4.1.png", screen);
	Skills.lightning.lightning1 = LoadImage("image/lightning0.png", screen);
	Skills.lightning.lightning2 = LoadImage("image/lightning1.png", screen);
	Skills.lightning.lightning3 = LoadImage("image/lightning2.png", screen);
	Skills.lightning.lightning4 = LoadImage("image/lightning3.png", screen);
	Skills.lightning.lightning5 = LoadImage("image/lightning4.png", screen);
	lightningSound = Mix_LoadWAV("image/lightningMusic.mp3");
	soundEffect = Mix_LoadWAV("image/Gun.wav");
	soundEffect1 = Mix_LoadWAV("image/Explore.wav");
	healthSound = Mix_LoadWAV("image/health.mp3");
	shield = LoadImage("image/khien.png", screen);
	shield1 = LoadImage("image/khien2.png", screen);
	shield2 = LoadImage("image/khien2.1.png", screen);
	skill2texture = LoadImage("image/skill2.png", screen);
	skill2Effecttexture = LoadImage("image/skill2effect.png", screen);
	heart = LoadImage("image/heart.png", screen);
	blackheart = LoadImage("image/blackheart.png", screen);
	back = LoadImage("image/back.png", screen);
	pause = LoadImage("image/pause.png", screen);
	replay = LoadImage("image/replay.png", screen);
	home1 = LoadImage("image/home.png", screen);
	font = TTF_OpenFont("font/b.ttf", 36);

}
void skill1() {
	if (Skills.skill1 == false) {
		checkCollision(); // chech va cham end game
	}
	else {
		shiledRect = { rectplane.x - 15, rectplane.y - 25, 80, 80 };
		Render(shield, screen, shiledRect);
		Skills.skillTime();
	}
}
void skill2() {
	if (Skills.skill2 == true) {
		frame++;
		for (int i = 0; i < enemies.size(); i++) {
			SDL_Rect rect;
			if (frame == 1) {
				if (i == 0) Mix_PlayChannel(-1, lightningSound, 0);
				rect = { enemies[i].x, enemies[i].y - 80, 50, 15 };
				Render(Skills.lightning.lightning1, screen, rect);
			}
			else if (frame == 2) {
				rect = { enemies[i].x, enemies[i].y - 80, 50, 26 };
				Render(Skills.lightning.lightning2, screen, rect);
			}
			else if (frame == 3) {
				rect = { enemies[i].x, enemies[i].y - 80, 50, 45 };
				Render(Skills.lightning.lightning3, screen, rect);
			}
			else if (frame == 4) {
				rect = { enemies[i].x, enemies[i].y - 80, 50, 65 };
				Render(Skills.lightning.lightning4, screen, rect);
			}
			else if (frame == 5) {
				rect = { enemies[i].x, enemies[i].y - 80, 50, 80 };
				Render(Skills.lightning.lightning5, screen, rect);
			}
			else break;
		}
		SDL_Delay(50);
		if (frame == 6) {
			int n = enemies.size();
			score += n;
			temp = score;
			frame = 0;
			Skills.timeSkill2 = time1;
			enemies.clear();
			Skills.skill2 = false;
		}
	}
}
void skill3() {
	if (Skills.skill3 == true) {
		if (healthRect.w <= 150) {
			healthRect.w += 50;
		}
		else {
			healthRect.w = 200;
		}
		Skills.timeSkill3 = time1;
		Skills.skill3 = false;
	}

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
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (play == false) {
					if (highestScore == false) {
						if (x >= start_.x && x <= start_.x + 250 && y >= start_.y && y <= start_.y + 60) {
							play = true;
						}
						else if (x >= exit_.x && x <= exit_.x + 250 && y >= exit_.y && y <= exit_.y + 60) {
							running = false;
						}
						else if (x >= score_.x && x <= score_.x + 250 && y >= score_.y && y <= score_.y + 60) {
							highestScore = true;
						}
					}
					else {
						if (x >= backRect.x && x <= backRect.x + 100 && y >= backRect.y && y <= backRect.y + 100) {
							highestScore = false;
						}
					}
				}
				else {
					if (pauseGame == false) {
						if (x >= pauseRect.x && x <= pauseRect.x + 30 && y >= pauseRect.y && y <= pauseRect.y + 30) {
							pauseGame = true;
						}
						else if (e.button.button == SDL_BUTTON_LEFT) {
							bullets.push_back(Bullet(rectplane.x + rectplane.w, rectplane.y + rectplane.h / 2 - 5, 1));
							Mix_PlayChannel(-1, soundEffect, 0);
						}
					}
					else {
						if (x >= backRect.x && x <= backRect.x + 80 && y >= backRect.y && y <= backRect.y + 80) {
							pauseGame = false;
						}
						if (x >= score_.x && x <= score_.x + 250 && y >= score_.y && y <= score_.y + 60) {
							cleanPlay(enemies, bullets, enemyBullet, rectplane, rectBG, time_);
							play = false;
							pauseGame = false;
						}
						if (x >= start_.x && x <= start_.x + 250 && y >= start_.y && y <= start_.y + 60) {
							cleanPlay(enemies, bullets, enemyBullet, rectplane, rectBG, time_);
							score = 0;
							play = true;
							pauseGame = false;
						}
					}
				}
			}
			else if (e.type == SDL_KEYDOWN) {
				// return to menu
				if (e.key.keysym.sym == SDLK_SPACE && scoreCheck == true) {
					score = 0;
					play = false;
					scoreCheck = false;
				}
				//choose skill
				if (time1 - Skills.timeSkill1 >= 10) {
					if (e.key.keysym.sym == SDLK_1 && Skills.skill1 == false) {
						Skills.skill1 = true;
						Skills.timeSkill1 = time1;
					}
				}
				if (time1 - Skills.timeSkill2 >= 30) {
					if (e.key.keysym.sym == SDLK_2 && Skills.skill2 == false) {
						Skills.skill2 = true;
					}
				}
				if (time1 - Skills.timeSkill3 >= 5) {
					if (e.key.keysym.sym == SDLK_3 && Skills.skill3 == false) {
						Skills.skill3 = true;
					}
				}
			}
		}
		if (play == false && scoreCheck == false) {
			if (highestScore == false) {
				Menu(screen, start, Exit, scoreTexture);
			}
			else {
				Render(bground, screen, rectBG);
				Render(back, screen, backRect);
				string scoreStr = "Highest Score: " + to_string(getHighestScore());
				SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreStr.c_str(), textColor);
				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
				SDL_Rect dstRect = { width / 2 - 200, heigh / 2 - 50, 400, 100 };
				SDL_RenderCopy(screen, textTexture, NULL, &dstRect);
				SDL_RenderPresent(screen);
				SDL_FreeSurface(textSurface);
				SDL_DestroyTexture(textTexture);
			}

			float current_time = SDL_GetTicks() / 1000;
			Skills.timeSkill1 = current_time;
			Skills.timeSkill2 = current_time;
			Skills.timeSkill3 = current_time;
		}
		else if (play == true && scoreCheck == false) {
			if (pauseGame == false) {
				time1 = SDL_GetTicks() / 1000;
				time_eplane(time1, time_, time2);
				fps_timer.start();
				Render(bground, screen, rectBG);
				scrollBackground(bground, screen, rectBG.x, 1);
				Render(plane, screen, rectplane);
				Render(hpTexture, screen, hpRect);
				Render(healthTexture, screen, healthRect);
				Render(pause, screen, pauseRect);
				if (time1 - Skills.timeSkill1 >= 10) {
					Render(shield1, screen, { 650, 0, 30, 30 });
				}
				else {
					Render(shield2, screen, { 650, 0, 30, 30 });
					string a = to_string(int(10 - (time1 - Skills.timeSkill1)));
					SDL_Surface* textSurface = TTF_RenderText_Solid(font, a.c_str(), textColor);
					SDL_Texture* textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
					SDL_Rect dstRect = { 655, 5, 20, 20 };
					SDL_RenderCopy(screen, textTexture, NULL, &dstRect);
					SDL_FreeSurface(textSurface);
					SDL_DestroyTexture(textTexture);
				}
				if (time1 - Skills.timeSkill2 >= 30) {
					Render(skill2Effecttexture, screen, { 700, 0, 30, 30 });
				}
				else {
					Render(skill2texture, screen, { 700, 0, 30, 30 });
					string a = to_string(int(30 - (time1 - Skills.timeSkill2)));
					SDL_Surface* textSurface = TTF_RenderText_Solid(font, a.c_str(), textColor);
					SDL_Texture* textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
					SDL_Rect dstRect = { 705, 5, 20, 20 };
					SDL_RenderCopy(screen, textTexture, NULL, &dstRect);
					SDL_FreeSurface(textSurface);
					SDL_DestroyTexture(textTexture);
				}
				if (time1 - Skills.timeSkill3 >= 60) {
					Render(heart, screen, { 750, 0, 30, 30 });
				}
				else {
					Render(blackheart, screen, { 750, 0, 30, 30 });
					string a = to_string(int(60 - (time1 - Skills.timeSkill3)));
					SDL_Surface* textSurface = TTF_RenderText_Solid(font, a.c_str(), textColor);
					SDL_Texture* textTexture = SDL_CreateTextureFromSurface(screen, textSurface);
					SDL_Rect dstRect = { 755, 5, 20, 20 };
					SDL_RenderCopy(screen, textTexture, NULL, &dstRect);
					SDL_FreeSurface(textSurface);
					SDL_DestroyTexture(textTexture);
				}
				// di chuyen may bay
				planemove(rectplane, planeSpeed);
				// dan may bay
				fire();
				// skill1
				skill1();
				// tao may bay dich
				createEnemies();
				// skill2
				skill2();
				// skill3
				skill3();
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
			else {
				SDL_Rect bg = { 0, 0, width, heigh };
				Render(bground, screen, bg);
				Render(back, screen, backRect);
				Render(home1, screen, score_);
				Render(replay, screen, start_);
				SDL_RenderPresent(screen);
			}
		}
		else {
			float current_time = SDL_GetTicks() / 1000;
			Skills.timeSkill1 = current_time;
			Skills.timeSkill2 = current_time;
			Skills.timeSkill3 = current_time;
			Render(bground, screen, rectBG);
			renderScore();
		}
	}
	cleanup();
	return 0;
}