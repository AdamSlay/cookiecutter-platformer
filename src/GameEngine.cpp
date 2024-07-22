#include <iostream>
#include <stdexcept>

#include "GameEngine.h"
#include "utils.h"

GameEngine::GameEngine() {
    /**
     * GameEngine constructor
     * Initialize SDL2, SDL2_ttf, SDL_image, and create a window and renderer
     */

    this->window = nullptr;
    this->renderer = nullptr;
    this->font = nullptr;
    if (Utils::initialize_resource(window, renderer, font) != 0) {
        throw std::runtime_error("Failed to initialize resources");
    }

    SDL_RaiseWindow(window);
    SDL_PumpEvents();
}

GameEngine::~GameEngine() {
    /**
     * GameEngine destructor
     * Close the window, renderer, and font. Quit SDL2, SDL2_ttf, and SDL2_image
     */

    Utils::close_resources(window, renderer, font);
}

void GameEngine::run() {
    /**
     * Main game loop
     */

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // TODO: render text to screen

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}