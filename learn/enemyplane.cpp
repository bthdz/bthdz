	
#include "enemyplane.h"

	bool checkpos(Eplane e, vector<Eplane> enemies) {
		for (int i = 0; i < enemies.size() - 1; i++) {
			if (e.y >= enemies[i].y - 50 && e.y <= enemies[i].y + 50) return false;
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
		vector <string> enemyTexture;
		for (int i = 1; i <= 3; i++) {
			string b;
			b = "image/plane" + to_string(i) + ".png";
			enemyTexture.push_back(b);
		}
		int a = (rand() % 2) + 1;
		string c = enemyTexture[a];
		return c;
	}

	void Eplane::EplaneMotion() {
		x -= speed;
	}

	void time_eplane(float time, int& time_, float &time1) {
		if (time - time1 >= 10 && time_ >= 20) {
			time_ -= 20;
			time1 = time;
		}
	}