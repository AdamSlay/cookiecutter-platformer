#pragma once
#ifndef COOKIECUTTERPLATFORMERER_UTILS_H
#define COOKIECUTTERPLATFORMERER_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace Utils {
  int initialize_resource(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font);
  void close_resources(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font);
}
#endif //COOKIECUTTERPLATFORMERER_UTILS_H
