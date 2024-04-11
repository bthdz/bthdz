#pragma once

#include "function.h"
#include "BaseObject.h"

void planemove(SDL_Rect &rect, float speed);
void keepIn(SDL_Rect& rect);

struct Timer
{
	int start_ticks;
	int paused_ticks;

	bool paused_;
	bool started_;

	Timer();
	void start();
	void stop();
	void paused();
	void unpaused();

	int get_ticks();

	bool is_started();
	bool is_paused();
};

static Timer fps_timer;