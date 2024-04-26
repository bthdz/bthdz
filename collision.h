#pragma once

#include "function.h"
#include "motion.h"
#include "enemyplane.h"

bool planeCollision(vector <Bullet> &a, SDL_Rect rect, vector <Eplane> &b, int & score);
void bulletCollision(vector <Bullet>& a, vector <Bullet>& b);
void EplaneCollision(vector<Bullet>& a, vector<Eplane>& b, vector<Bullet>& enemyBullets, int &score, Mix_Chunk* &soundEffect1);
