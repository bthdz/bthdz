//
//#include <bits/stdc++.h>
//#include <SDL.h>
//#include <SDL_mixer.h>
//
//int main(int argc, char** argv) {
//    // Initialize SDL
//    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
//
//    // Create a window
//    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
//
//    // Create a renderer
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//
//    // Initialize SDL_Mixer
//    Mix_Init(MIX_INIT_MP3);
//    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
//
//    // Load the sound file
//    Mix_Music* music = Mix_LoadMUS("image/Music_bgr.mp3");
//
//    // Main loop
//    bool quit = false;
//    SDL_Event event;
//    while (!quit) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                quit = true;
//            }
//            else if (event.type == SDL_KEYDOWN) {
//                if (event.key.keysym.sym == SDLK_p) {
//                    // Play the sound file
//                    std::cerr << "P\n";
//                    std::cerr << Mix_PlayMusic(music, 1);
//                }
//            }
//        }
//
//        // Clear the renderer
//        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
//        SDL_RenderClear(renderer);
//
//        // Update the renderer
//        SDL_RenderPresent(renderer);
//    }
//    std::cerr << "OK";
//    // Clean up
//    Mix_FreeMusic(music);
//    Mix_CloseAudio();
//    Mix_Quit();
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}