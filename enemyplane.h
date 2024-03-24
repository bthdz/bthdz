#pragma once

#include "move.h"

struct Eplane
{
	int x, y;
	int w, h;
	int speed = 0;
	float timeshoot;
	int bulletDistance;
	vector<Bullet> Ebullets;
	Eplane( int b, int c) {
		w = b;
		h = c;
	}
	void createpos() {
		x = width;
		y = rand() % (heigh - h);
	}
	void createspeed() {
		timeshoot = rand() % (200 - 50) + 50;
		speed = (rand() % 2) + 1;
		bulletDistance = rand() % (1000 - 400) + 400;
	}
	void shoot() {
		if (Ebullets.size() == 0) {
			Ebullets.push_back(Bullet(x, y + h / 2 - 5, bulletspeed));
		}
		else if(abs(Ebullets[Ebullets.size() -1].x - x) >= timeshoot) {
			Ebullets.push_back(Bullet(x, y + h / 2 - 5, bulletspeed));
		}
		for (size_t i = 0; i < Ebullets.size(); i++) {
			Ebullets[i].x -= bulletspeed;
			SDL_Rect rect = { Ebullets[i].x , Ebullets[i].y, 20, 10 };
			Render(bulletTexture, screen, rect);
			if (abs(Ebullets[i].x - x) >= bulletDistance) {
				Ebullets.erase(Ebullets.begin()+i);
				i--;
			}
		}
	}
};
bool check(Eplane e, vector <Eplane> Ep);
