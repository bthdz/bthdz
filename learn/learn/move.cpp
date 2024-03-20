#include "move.h"

void planemove(SDL_Rect &rect, float speed, float delta) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W])
    {
        rect.y -= speed;
    }
    else if (currentKeyStates[SDL_SCANCODE_S])
    {
        rect.y += speed  ;
    }
    else if (currentKeyStates[SDL_SCANCODE_A])
    {
        rect.x -= speed ;
    }
    else if (currentKeyStates[SDL_SCANCODE_D])
    {
        rect.x += speed ;
    }
}






  