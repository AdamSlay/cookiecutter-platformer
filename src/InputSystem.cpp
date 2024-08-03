#include <iostream>
#include <fstream>
#include <unordered_map>

#include <nlohmann/json.hpp>
#include <SDL2/SDL.h>

#include "InputSystem.h"

using json = nlohmann::json;

InputSystem::InputSystem() {
    loadInputMaps();
}

void InputSystem::update(bool &quit) {
    /**
     * Update the input system
     *
     * @param entityManager: The entity manager
     * @param quit: The quit flag
     */
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            quit = true;
        }
    }
}

void InputSystem::loadInputMaps() {
    /**
     * Load input maps
     */

    loadScancodeMap("etc/input_maps/keyboard_map.json");
    loadControllerMap("etc/input_maps/controller_map.json");
}

void InputSystem::loadScancodeMap(const std::string& filePath) {
    /**
     * Load scancode map from file
     *
     * @param filePath: The path to the scancode map file
     */

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open keyboard map file: " + filePath);
    }
    json j;
    file >> j;
    for (auto& element : j.items()) {
        SDL_Scancode scancode = SDL_GetScancodeFromName(element.key().c_str());
        std::string action = element.value();
        keyboardMap[scancode] = action;
    }
}

void InputSystem::loadControllerMap(const std::string& filePath) {
    /**
     * Load controller map from file
     *
     * @param filePath: The path to the controller map file
     */

    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open controller map file: " + filePath);
    }
    json j;
    file >> j;
    for (auto& element : j.items()) {
        SDL_GameControllerButton button = SDL_GameControllerGetButtonFromString(element.key().c_str());
        std::string action = element.value();
        controllerMap[button] = action;
    }
}

void InputSystem::handleKeyboardInput(SDL_Event& e) {
    /**
     * Handle Keyboard input
     *
     * @param e: The SDL event
     * @param input: The input component
     */

    keyStates[e.key.keysym.scancode] = (e.type == SDL_KEYDOWN);
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        auto it = keyboardMap.find(e.key.keysym.scancode);
        if (it != keyboardMap.end()) {
            justPressed[e.key.keysym.scancode] = true;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        auto it = keyboardMap.find(e.key.keysym.scancode);
        if (it != keyboardMap.end()) {
            justReleased[e.key.keysym.scancode] = true;
        }
    }
}

void InputSystem::handleControllerInput(SDL_Event& e) {
    /**
     * Handle Controller input
     *
     * @param e: The SDL event
     * @param input: The input component
     */
    SDL_Scancode scancode = mapControllerButtonToScancode(e.cbutton.button);
    auto button = static_cast<SDL_GameControllerButton>(e.cbutton.button);
    keyStates[scancode] = (e.type == SDL_CONTROLLERBUTTONDOWN);
    if (e.type == SDL_CONTROLLERBUTTONDOWN) {
        auto it = controllerMap.find(button);
        if (it != controllerMap.end()) {
            justPressed[scancode] = true;
        }
    }
    else if (e.type == SDL_CONTROLLERBUTTONUP) {
        auto it = controllerMap.find(button);
        if (it != controllerMap.end()) {
            justReleased[scancode] = true;
        }
    }

}

void InputSystem::handleJoystickInput(SDL_Event& e) {
    /**
     * Handle Joystick input
     *
     * @param e: The SDL event
     * @param input: The input component
     */
    if (e.jaxis.axis == 0) { // X axis
        joystickDirection.first = e.jaxis.value / 32767.0f;
        if (joystickDirection.first < -deadZone) {
            keyStates[SDL_SCANCODE_LEFT] = true;
            keyStates[SDL_SCANCODE_RIGHT] = false;
        } else if (joystickDirection.first > deadZone) {
            keyStates[SDL_SCANCODE_RIGHT] = true;
            keyStates[SDL_SCANCODE_LEFT] = false;
        } else {
            keyStates[SDL_SCANCODE_RIGHT] = false;
            keyStates[SDL_SCANCODE_LEFT] = false;
        }
    }
    if (e.jaxis.axis == 1) { // Y axis
        joystickDirection.second = e.jaxis.value / 32767.0f;
        if (joystickDirection.second < -deadZone) {
            keyStates[SDL_SCANCODE_UP] = true;
            keyStates[SDL_SCANCODE_DOWN] = false;
        } else if (joystickDirection.second > deadZone) {
            keyStates[SDL_SCANCODE_DOWN] = true;
            keyStates[SDL_SCANCODE_UP] = false;
        } else {
            keyStates[SDL_SCANCODE_DOWN] = false;
            keyStates[SDL_SCANCODE_UP] = false;
        }
    }
}

SDL_Scancode InputSystem::mapControllerButtonToScancode(Uint8 button) {
    /**
     * Map controller buttons to keyboard inputs
     *
     * @param button: The controller button
     */
    switch (button) {
        case SDL_CONTROLLER_BUTTON_A:
            return SDL_SCANCODE_UP; // Map 'A' button to up key
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:  // Map 'X' button to Space key
            return SDL_SCANCODE_SPACE;
        case SDL_CONTROLLER_BUTTON_X:
            return SDL_SCANCODE_R;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            return SDL_SCANCODE_LEFT; // Map left D-pad button to left arrow key
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            return SDL_SCANCODE_RIGHT; // Map right D-pad button to right arrow key
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            return SDL_SCANCODE_DOWN;  // Map down D-pad button to down arrow key
        default:
            return SDL_SCANCODE_UNKNOWN;
    }
}