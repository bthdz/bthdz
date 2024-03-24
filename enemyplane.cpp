#include "enemyplane.h"

bool check(Eplane e, vector<Eplane> Ep) {
	for (int i = 0; i < Ep.size() - 1; i++) {
		if (e.y >= Ep[i].y - 50 && e.y <= Ep[i].y + 50) return false;
	}
	return true;
}

