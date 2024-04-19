	
#include "enemyplane.h"

	bool checkpos(Eplane e, vector<Eplane> enemies) {
		for (int i = 0; i < enemies.size() - 1; i++) {
			if (e.y >= enemies[i].y - 20 && e.y <= enemies[i].y + 20) return false;
		}
		return true;
	}

	void Eplane::createpos() {
		x = width - 30;
		y = rand() % (heigh - h);
	}

	void Eplane::createspeed() {
		timeshoot = rand() % (200 - 50) + 50;
		speed = rand() % 2 + 2;
		bulletDistance = rand() % (1000 - 400) + 400;
	}

	string Eplane::randomEnemy() {
		enemyTexture.push_back("image/plane1.png");
		enemyTexture.push_back("image/plane2.png");
		enemyTexture.push_back("image/plane3.png");
		int a = rand() % 3;
		string c = enemyTexture[a];
		return c;
	}

	void Eplane::EplaneMotion() {
		x -= speed;
	}

	void time_eplane(float time1, int& time_, float &time2) {
		if (time1 - time2 >= 10 && time_ >= 20) {
			time_ -= 10;
			time2 = time1;
		}
	}