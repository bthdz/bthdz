
#include "enemyplane.h"



bool init() {
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

int main(int argv, char* argc[]) {
	if (!init()) {
		cout << "loi cua so: " << SDL_GetError();
		return -1;
	}

	bground = LoadImage("image/sky1.jpg", screen);
	plane = LoadImage("image/maybay.png", screen);
	bulletTexture = LoadImage("image/bullet16x5.png", screen);
	SDL_Texture* plane1;
	plane1 = LoadImage("image/maybay1.png", screen);
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
	Eplane enemies;
	enemies.createPos();
	enemies.timeshoot = 400;
	enemies.lastTimefire = SDL_GetTicks();

	SDL_Rect rectenemies = { enemies.x, enemies.y, 100, 100 };
	Uint32 lastTime = SDL_GetTicks();
	bool running = true;
	while (running) {
		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime);
		lastTime = currentTime;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_SPACE) {
					bullets.push_back(Bullet(rectplane.x + rectplane.w, rectplane.y + rectplane.h/2 - 5, bulletspeed));
					cout << deltaTime << endl;
				}
			}
		}
		planemove(rectplane, speed, deltaTime);
		keepIn(rectplane);
		Render(bground, screen, rectBG);
		Render(plane, screen, rectplane);
		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].x += bulletspeed * deltaTime;
			SDL_Rect rectbullet = { bullets[i].x, bullets[i].y, 30, 10};
			Render(bulletTexture, screen, rectbullet);
			if (bullets[i].x > width - 30) {
				bullets.erase(bullets.begin() + i);
				i--;
			}
		}

		enemies.createBullet(currentTime);
		enemies.x -= speed * deltaTime/10;
		if (enemies.x <= 0) {
			srand(time(NULL));
			enemies.createPos();
		}
		SDL_Rect rectenemies = { enemies.x, enemies.y, 100, 100 };
		Render(plane1, screen, rectenemies);
		for (size_t i = 0; i < enemies.enemyBullets.size(); ++i) {
	
			enemies.enemyBullets[i].x -= (bulletspeed*deltaTime/5);
			SDL_Rect rectEbullet = { enemies.enemyBullets[i].x , enemies.enemyBullets[i].y, 30, 10 };
			Render(bulletTexture, screen, rectEbullet);
			if (enemies.enemyBullets[i].x <= 0) {
				enemies.enemyBullets.erase(enemies.enemyBullets.begin() + i);
				i--;
			}
		}
		SDL_RenderPresent(screen);
	}
	cleanup();
	return 0;
}

