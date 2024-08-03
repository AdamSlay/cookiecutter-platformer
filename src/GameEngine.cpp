#include <iostream>
#include <stdexcept>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "GameEngine.h"
#include "RenderSystem.h"
#include "InputSystem.h"

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
    InputSystem inputSystem;
    RenderSystem renderSystem(renderer);

    bool quit = false;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    float deltaTime = 0.0f;

    while (!quit) {

        // frame timing
        increment_time(lastTime, deltaTime);

        // handle events
        // entities handle input. give them an input component that holds info about the source of their input stream
        // they listen to that stream and update their state according to the input
        // the stream could be a keyboard, mouse, controller, or the AI system

        // ^^^ not sure about that. You could do global input handling, just take in what ever input is coming in from the hardware
        // the input handler funnels commands to the entities that correspond to the input source(player 1, player 2, etc)
        // entities have an input component that holds a reference to the input source that gets assiged to it
        // input sources get assigned when they are detected
        inputSystem.update(quit);

        // update systems
        renderSystem.update();
    }
}

int GameEngine::initialize_resources() {
    /**
     * Initialize SDL2, SDL2_image, SDL2_mixer and SDL2_ttf
     */

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not be initialized. \nSDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize window
    std::string title = config.getWindowTitle();
    int width = config.getWindowWidth();
    int height = config.getWindowHeight();
    window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height,SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created. \nSDL Error: " << SDL_GetError() << std::endl;
        return 2;
    }

    // Initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be initialized. \nSDL Error: " << SDL_GetError() << std::endl;
        return 3;
    }

    // Initialize Image loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not be initialized. \nSDL_Image Error: " << IMG_GetError() << std::endl;
        return 4;
    }

    // Initialize TTF font loading
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not be initialized. \nSDL_TTF Error: " << TTF_GetError() << std::endl;
        return 5;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not be initialized. \nSDL_mixer Error: " << Mix_GetError() << std::endl;
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
    SDL_Delay(100);  // Delay allows Mix_CloseAudio() to complete and avoid "blip" sound

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void GameEngine::increment_time(Uint32& lastTime, float& deltaTime) {
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
}
