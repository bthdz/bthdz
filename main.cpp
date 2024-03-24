
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

void createEplane(vector <Eplane>& Ep) {
	if (Ep.size() == 0) {
		Eplane a(50, 50);
		a.createpos();
		a.createspeed();
		Ep.push_back(a);
	}
	else if (Ep[Ep.size() - 1].x < width - 100) {
		Eplane a(50, 50);
		a.createpos();
		a.createspeed();
		Ep.push_back(a);
	}
	for (size_t i = 0; i < Ep.size(); i++) {
		Ep[i].x -= Ep[i].speed;
		if (Ep.size() >= 2 && i == Ep.size() - 1) {
			if (check(Ep[i], Ep)) {
				SDL_Rect rect = { Ep[i].x, Ep[i].y, Ep[i].w, Ep[i].h };
				Render(eplane, screen, rect);
				Ep[i].shoot();
			}
			else {
				Ep.erase(Ep.begin() + i);
				i--;
			}
		}
		else {
			SDL_Rect rect = { Ep[i].x, Ep[i].y, Ep[i].w, Ep[i].h };
			Render(eplane, screen, rect);
			Ep[i].shoot();
		}
		if (Ep[i].x <= 0) {
			Ep.erase(Ep.begin() + i);
			i--;
		}
	}
}


int main(int argv, char* argc[]) {
	if (!init()) {
		cout << "loi cua so: " << SDL_GetError();
		return -1;
	}

	bground = LoadImage("image/bg.jpg", screen);
	plane = LoadImage("image/plane1.png", screen);
	bulletTexture = LoadImage("image/bullet16x5.png", screen);
	eplane = LoadImage("image/maybay1.png", screen);
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

	vector <Eplane> enemies;

	bool running = true;
	while (running) {
		SDL_Delay(5);
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			else if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_SPACE) {
					bullets.push_back(Bullet(rectplane.x + rectplane.w, rectplane.y + rectplane.h/2 - 5, 1));
				}
			}
		}
		planemove(rectplane, planeSpeed);
		keepIn(rectplane);
		Render(bground, screen, rectBG);
		Render(plane, screen, rectplane);
		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].x += bulletspeed;
			SDL_Rect rectbullet = { bullets[i].x, bullets[i].y, 5, 5 };
			SDL_Rect rectbullet2 = { bullets[i].x, bullets[i].y + 15, 5, 5 };
			SDL_Rect rectbullet3 = { bullets[i].x, bullets[i].y - 15, 5, 5 };
			Render(bulletTexture, screen, rectbullet);
			Render(bulletTexture, screen, rectbullet2);
			Render(bulletTexture, screen, rectbullet3);
			if (bullets[i].x > width) {
				bullets.erase(bullets.begin()+i);
				i--;
			}
		}
		createEplane(enemies);
		SDL_RenderPresent(screen);

	}
	cleanup();
	return 0;
}

