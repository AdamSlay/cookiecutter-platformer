#ifndef COOKIECUTTER_PLATFORMER_GAMEENGINE_H
#define COOKIECUTTER_PLATFORMER_GAMEENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class GameEngine {
public:
    GameEngine(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
};


#endif //COOKIECUTTER_PLATFORMER_GAMEENGINE_H
