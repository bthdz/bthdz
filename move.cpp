#include "move.h"

void planemove(SDL_Rect &rect, float planeSpeed) {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_UP])
    {
        rect.y -= static_cast<int>(planeSpeed );
    }
    if (currentKeyStates[SDL_SCANCODE_DOWN])
    {
        rect.y += static_cast<int>(planeSpeed);
    }
    if (currentKeyStates[SDL_SCANCODE_LEFT])
    {
        rect.x -= static_cast<int>(planeSpeed );
    }
    if (currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        rect.x += static_cast<int>(planeSpeed );
    }
  
}






  