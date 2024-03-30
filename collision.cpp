#include "collision.h"

bool planeCollision(vector <Bullet> a, SDL_Rect rect, vector<Eplane> b) {
    // va cham voi dan
	for (size_t i = 0; i < a.size(); i++) {
		if (a[i].x <= rect.x + rect.w/2 && a[i].x >= rect.x - bulletwidth && a[i].y > rect.y - bulletheigh && a[i].y < rect.y + rect.h) {
			return true;
		}
	}
    // va cham voi may bay dich
	for (size_t i = 0; i < b.size(); i++) {
		if (b[i].x <= rect.x + rect.w / 2 && b[i].x > rect.x - Eplanewidth/2 && b[i].y > rect.y - Eplaneheigh && b[i].y < rect.y + rect.h) {
			return true;
		}
	}
	return false;
}
void bulletCollision(vector<Bullet>& a, vector<Bullet>& b) {
    vector<int> DeleteA;
    vector<int> DeleteB;

    for (int i = 0; i < a.size(); i++) {
        int c = 0;
        for (int j = 0; j < b.size(); j++) {
            if (a[i].x + bulletwidth >= b[j].x && a[i].x < b[j].x + bulletwidth &&  a[i].y + bulletheigh > b[j].y && a[i].y < b[j].y + bulletheigh) {
                DeleteB.push_back(j);
                c = 1;
            }
        }
        if (c == 1) DeleteA.push_back(i);
    }
     
    for (int i = DeleteA.size() - 1; i >= 0; i--) {
        a.erase(a.begin() + DeleteA[i]);
    }

    for (int j = DeleteB.size() - 1; j >= 0; j--) {
        b.erase(b.begin() + DeleteB[j]);
    }

}

void EplaneCollision(vector<Bullet>& a, vector<Eplane>& b, vector<Bullet>& enemyBullets) {
    vector<int> DeleteB;
    vector<int> DeleteA;
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            if (a[i].x + bulletwidth > b[j].x && a[i].x < b[j].x + Eplanewidth && a[i].y + bulletheigh > b[j].y && a[i].y < b[j].y + Eplaneheigh) {
                DeleteB.push_back(j);
                DeleteA.push_back(i);
                break;
            }
        }
    }
    for (int i = DeleteA.size() - 1; i >= 0; i--) {
        a.erase(a.begin() + DeleteA[i]);
    }
    for (int j = DeleteB.size() - 1; j >= 0; j--) {
        for (size_t i = 0; i < b[DeleteB[j]].Ebullets.size(); i++) {
            enemyBullets.push_back(b[DeleteB[j]].Ebullets[i]);
        }
    }
    for (int j = DeleteB.size() - 1; j >= 0; j--) {
        b.erase(b.begin() + DeleteB[j]);
    }
}





