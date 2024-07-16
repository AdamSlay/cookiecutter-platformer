#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

std::string FONT_PATH = "../assets/SuperFunky.ttf";
int FONT_SIZE = 50;
int SCREEN_WIDTH = 740;
int SCREEN_HEIGHT = 420;

namespace Utils {

int initialize_resource(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font) {
    /**
     * Initialize SDL2, SDL2_image, SDL2_mixer and SDL2_ttf
     */

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize window
    window = SDL_CreateWindow("BummerEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window could not be created! \nError: " << SDL_GetError() << std::endl;
        return 2;
    }

    // Initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cout << "Renderer could not be initialized! \nError: " << SDL_GetError() << std::endl;
        return 3;
    }

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not be initialized! \nError: " << IMG_GetError() << std::endl;
        return 4;
    }

    // Initialize TTF font loading
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! \nError: " << TTF_GetError() << std::endl;
        return 5;
    }

    // Load font
    font = TTF_OpenFont(FONT_PATH.c_str(), FONT_SIZE);
    if (font == nullptr) {
        std::cout << "Failed to load font! \nError: " << TTF_GetError() << std::endl;
        return 6;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 7;
    }
    return 0;
  }


  void close_resources(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font) {
      /**
       * Free renderer, window, and font
       * Quit SDL2, SDL2_ttf, SDL2_mixer and SDL2_image
       */

      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      renderer = nullptr;
      window = nullptr;
      font = nullptr;

      Mix_CloseAudio();
      SDL_Delay(100);  // Delay to allow Mix_CloseAudio() to complete to avoid "blip" sound

      IMG_Quit();
      TTF_Quit();
      Mix_Quit();
      SDL_Quit();
  }

}

