#ifndef COOKIECUTTER_PLATFORMER_RENDERSYSTEM_H
#define COOKIECUTTER_PLATFORMER_RENDERSYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class RenderSystem {
public:
    RenderSystem(SDL_Renderer* renderer);
    void draw_text(const std::string& text, int x, int y, TTF_Font* font, SDL_Color color, int wrapLength);
private:
    SDL_Renderer* renderer = nullptr;
};


#endif //COOKIECUTTER_PLATFORMER_RENDERSYSTEM_H
