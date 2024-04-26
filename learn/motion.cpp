#include "motion.h"

void planemove(SDL_Rect &rect, float planeSpeed) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        rect.y -= planeSpeed;
    }
    if (currentKeyStates[SDL_SCANCODE_S])
    {
        rect.y += planeSpeed;
    }
    if (currentKeyStates[SDL_SCANCODE_A])
    {
        rect.x -= planeSpeed;
    }
    if (currentKeyStates[SDL_SCANCODE_D])
    {
        rect.x +=planeSpeed ;
    } 
    keepIn(rect);
}

void keepIn(SDL_Rect& rect) {
    if (rect.x < 0) rect.x = 0;
    if (rect.x > width - rect.w) rect.x = width - rect.w;
    if (rect.y <= 20) rect.y = 20;
    if (rect.y > heigh - rect.h) rect.y = heigh - rect.h;
}

Timer::Timer()
{
    start_ticks = 0;
    paused_ticks = 0;
    started_ = false;
    paused_ = false;
}

void Timer::start() {
    started_ = true;
    paused_ = false;
    start_ticks = SDL_GetTicks();
}

void Timer::stop() {
    paused_ = false;
    started_ = false;
}

void Timer::paused() {
    if (started_ == true && paused_ == false) {
        paused_ = true;
        paused_ticks = SDL_GetTicks() - start_ticks;
    }
}

void Timer::unpaused() {
    if (paused_ == true) {
        paused_ = false;
        start_ticks = SDL_GetTicks() - paused_ticks;
        paused_ticks = 0;
    }
}

int Timer::get_ticks() {
    if (started_ == true) {
        if (paused_ == true) {
            return paused_ticks;
        }
        else return SDL_GetTicks() - start_ticks;
    }
    return 0;
}

bool Timer::is_started() {
    return started_;
}

bool Timer::is_paused() {
    return paused_;
}

  