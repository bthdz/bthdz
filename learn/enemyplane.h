#pragma once

#include "function.h"
#include "BaseObject.h"
#include "motion.h"

struct Eplane
{
	int x, y;
	int w, h;
	int speed = 0;
	float timeshoot;
	int bulletDistance;
	SDL_Texture* eplane = NULL;
	vector<Bullet> Ebullets;
	Eplane( int b, int c) {
		w = b;
		h = c;
	}
	void createpos();
	void createspeed();
	void EplaneMotion();
	void shoot() {
		if (Ebullets.size() == 0) {
			Ebullets.push_back(Bullet(x, y + h / 2 - 5, bulletspeed));
		}
		else if (abs(Ebullets[Ebullets.size() - 1].x - x) >= timeshoot) {
			Ebullets.push_back(Bullet(x, y + h / 2 - 5, bulletspeed));
		}
		for (int i = 0; i < Ebullets.size(); i++) {
			SDL_Rect rect = { Ebullets[i].x , Ebullets[i].y, bulletwidth, bulletheigh };
			Ebullets[i].x -= bulletspeed;
			Render(bulletTexture, screen, rect);
			if (abs(Ebullets[i].x - x) >= bulletDistance) {
				Ebullets.erase(Ebullets.begin() + i);
				i--;
			}
		}
	}
	string randomEnemy();
};

static vector <Bullet> enemyBullet;
static vector <Eplane> enemies; 

bool checkpos(Eplane e, vector <Eplane> Ep);
void time_eplane(float time, int& time_, float& time1);