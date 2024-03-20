#pragma once

#include "move.h"

struct Eplane
{
	int x, y;
	int timeshoot;
	Uint32 lastTimefire;
	vector <Bullet> enemyBullets;
	void createPos() {
		y = rand() % (heigh - 100);
		x = width;
	}
	void createBullet(Uint32 now) {
		if (now - lastTimefire >= timeshoot) {
			enemyBullets.push_back(Bullet(x, y + 45, bulletspeed));
			lastTimefire = now;
		}
	}
};

