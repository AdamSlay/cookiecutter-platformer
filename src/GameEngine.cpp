#include <iostream>
#include <stdexcept>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "GameEngine.h"
#include "RenderSystem.h"

GameEngine::GameEngine() {
    /**
     * GameEngine constructor
     * Initialize SDL2, SDL2_ttf, SDL_image, and create a window and renderer
     */

    if (initialize_resources() != 0) {
        throw std::runtime_error("Failed to initialize Game Engine resources");
    }
}

GameEngine::~GameEngine() {
    /**
     * GameEngine destructor
     * Close the window, renderer, and font. Quit SDL2, SDL2_ttf, and SDL2_image
     */

    close_resources();
}

void GameEngine::run() {
    /**
     * Main game loop
     */
    // Initialize Systems
    RenderSystem renderSystem(renderer);

    // Game Loop vars
    bool quit = false;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    // Game Loop
    while (!quit) {

        // handle frame timing
        std::tie(lastTime, deltaTime) = increment_time(lastTime, deltaTime);

        // handle events
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // reset canvas
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // draw current frame to canvas
        TTF_Font *font = load_font("assets/fonts/SuperFunky.ttf", 24);
        renderSystem.draw_text("Cookiecutter-Platformer", 100, 100, font, {255, 0, 0, 255}, 400);

        // present canvas
        SDL_RenderPresent(renderer);
    }
}

int GameEngine::initialize_resources() {
    /**
     * Initialize SDL2, SDL2_image, SDL2_mixer and SDL2_ttf
     */

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize window
    std::string title = config.getWindowTitle();
    int width = config.getWindowWidth();
    int height = config.getWindowHeight();
    window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! \nError: " << SDL_GetError() << std::endl;
        return 2;
    }

    // Initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be initialized! \nError: " << SDL_GetError() << std::endl;
        return 3;
    }

    // Initialize Image loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not be initialized! \nError: " << IMG_GetError() << std::endl;
        return 4;
    }

    // Initialize TTF font loading
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! \nError: " << TTF_GetError() << std::endl;
        return 5;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 7;
    }

    SDL_RaiseWindow(window);
//    SDL_PumpEvents();
    return 0;
}


void GameEngine::close_resources() {
    /**
     * Free renderer, window, and font
     * Quit SDL2, SDL2_ttf, SDL2_mixer and SDL2_image
     */

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;

    Mix_CloseAudio();
    SDL_Delay(100);  // Delay to allow Mix_CloseAudio() to complete to avoid "blip" sound

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

std::tuple<Uint32, float> GameEngine::increment_time(Uint32 lastTime, float deltaTime) {
    /**
     * Increment time between frames
     *
     * @param lastTime: The time of the last frame
     * @param deltaTime: The time between frames
     */
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    if (deltaTime < 1000 / 60) {
        SDL_Delay((1000 / 60) - deltaTime);
    }
    return {lastTime, deltaTime};
}

TTF_Font* GameEngine::load_font(std::string fontPath, int fontSize) {
    /**
     * Load a font from a file
     *
     * @param fontPath: The path to the font file
     * @param fontSize: The size of the font
     */
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Failed to load font! \nError: " << TTF_GetError() << std::endl;
    }
    return font;
}