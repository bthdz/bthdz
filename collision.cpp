#include "collision.h"

bool planeCollision(vector <Bullet> &a, SDL_Rect rect, vector<Eplane> &b, int & score) {
    // va cham voi dan
	for (size_t i = 0; i < a.size(); i++) {
		if (a[i].x <= rect.x + rect.w/2 && a[i].x >= rect.x - bulletwidth && a[i].y > rect.y - bulletheigh && a[i].y < rect.y + rect.h) {
            a.erase(a.begin() + i);
            i--;
			return true;
		}
	}
    // va cham voi may bay dich
	for (size_t i = 0; i < b.size(); i++) {
		if (b[i].x <= rect.x + rect.w / 2 && b[i].x > rect.x - Eplanewidth/2 && b[i].y > rect.y - Eplaneheigh && b[i].y < rect.y + rect.h) {
            for (int j = 0; j < b[i].Ebullets.size(); j++) {
                enemyBullet.push_back(b[i].Ebullets[j]);
            }
            b.erase(b.begin() + i);
            i--;
            Mix_PlayChannel(-1, soundEffect1, 0);
            score++;
            return true;
		}
	}
	return false;
}
void bulletCollision(vector<Bullet>& a, vector<Bullet>& b) {
    vector<int> DeleteA;
    vector<int> DeleteB;
    // dan va cham voi dan 
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            if (a[i].x + bulletwidth >= b[j].x && a[i].x < b[j].x + bulletwidth &&  a[i].y + bulletheigh > b[j].y && a[i].y < b[j].y + bulletheigh) {
                DeleteB.push_back(j);
                DeleteA.push_back(i);
                break;
            }
        }
    }
     
    for (auto it = DeleteA.rbegin(); it != DeleteA.rend(); ++it) {
        a.erase(a.begin() + *it);
    }

    sort(DeleteB.begin(), DeleteB.end());
    DeleteB.erase(unique(DeleteB.begin(), DeleteB.end()), DeleteB.end());

    for (auto it = DeleteB.rbegin(); it != DeleteB.rend(); ++it) {
        b.erase(b.begin() + *it);
    }

}

void EplaneCollision(vector<Bullet>& a, vector<Eplane>& b, vector<Bullet>& enemyBullets, int &score, Mix_Chunk* &soundEffect1) {
    vector<int> DeleteA;
    vector<int> DeleteB;
    // dan va cham may bay dich
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            if (a[i].x + bulletwidth > b[j].x && a[i].x < b[j].x + Eplanewidth && a[i].y + bulletheigh > b[j].y && a[i].y < b[j].y + Eplaneheigh) {
                DeleteB.push_back(j);
                DeleteA.push_back(i);
                Mix_PlayChannel(-1, soundEffect1, 0);
                break;
            }
        }
    }
    for (auto it = DeleteA.rbegin(); it != DeleteA.rend(); ++it) {
        a.erase(a.begin() + *it);
    }
    // giu lai nhung vien dan da ban
    for (int j = DeleteB.size() - 1; j >= 0; j--) {
        for (size_t i = 0; i < b[DeleteB[j]].Ebullets.size(); i++) {
            enemyBullets.push_back(b[DeleteB[j]].Ebullets[i]);
        }
    }
    for (auto it = DeleteB.rbegin(); it != DeleteB.rend(); ++it) {
        b.erase(b.begin() + *it);
        score++;
    }
}





