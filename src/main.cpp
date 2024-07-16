#include <iostream>

#include "utils.h"


using namespace Utils;


int main()
{
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  TTF_Font* font = nullptr;
  if (Utils::initialize_resource(window, renderer, font) != 0) {
    std::cerr << "Failed to initialize resources" << std::endl;
    return 1;
  }
  
  SDL_RaiseWindow(window);
  SDL_PumpEvents();
 
  // TODO: game_loop() 
  
  SDL_Delay(4000);
  Utils::close_resources(window, renderer, font); 
  
  return 0;
}

