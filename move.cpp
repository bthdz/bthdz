#include "move.h"

void planemove(SDL_Rect &rect, float planeSpeed) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        rect.y -= planeSpeed;
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        rect.y += planeSpeed;
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        rect.x -= planeSpeed;
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        rect.x +=planeSpeed ;
    } 
}






  