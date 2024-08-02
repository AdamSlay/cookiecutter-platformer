#ifndef COOKIECUTTER_PLATFORMER_GAMEENGINE_H
#define COOKIECUTTER_PLATFORMER_GAMEENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "ConfigManager.h"


class GameEngine {
public:
    GameEngine();
    ~GameEngine();
    void run();

private:
    ConfigManager& config = ConfigManager::getInstance();
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    int initialize_resources();
    void close_resources();
    void increment_time(Uint32& lastTime, float& deltaTime);
};


#endif //COOKIECUTTER_PLATFORMER_GAMEENGINE_H
