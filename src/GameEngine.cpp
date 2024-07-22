#include "GameEngine.h"

GameEngine::GameEngine(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font)
    : window(window), renderer(renderer), font(font) {

    SDL_RaiseWindow(window);
    SDL_PumpEvents();
}

void GameEngine::run() {
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}