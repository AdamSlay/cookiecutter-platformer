#ifndef COOKIECUTTER_PLATFORMER_INPUTSYSTEM_H
#define COOKIECUTTER_PLATFORMER_INPUTSYSTEM_H

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

enum class Action
{
    JUMP,
    MOVE_LEFT,
    MOVE_RIGHT,
    IDLE,
    STOP_JUMP
};


class InputSystem {
public:
    InputSystem();
    void update(bool& quit);

private:
    std::unordered_map<SDL_Scancode, Action> keyboardMap;
    std::unordered_map<SDL_GameControllerButton, Action> controllerMap;
    float deadZone = 0.3f;
    std::unordered_map<SDL_Scancode, bool> keyStates;
    std::unordered_map<SDL_Scancode, bool> justPressed;
    std::unordered_map<SDL_Scancode, bool> justReleased;
    std::pair<float, float> joystickDirection;

    void loadInputMaps();
    void loadControllerMap(const std::string& filepath);
    void loadScancodeMap(const std::string& filepath);
    void handleKeyboardInput(SDL_Event& e);
    void handleControllerInput(SDL_Event& e);
    void handleJoystickInput(SDL_Event& e);
    Action stringToAction(const std::string& actionString);
    static SDL_Scancode mapControllerButtonToScancode(Uint8 button);
};


#endif //COOKIECUTTER_PLATFORMER_INPUTSYSTEM_H
