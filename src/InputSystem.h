#ifndef COOKIECUTTER_PLATFORMER_INPUTSYSTEM_H
#define COOKIECUTTER_PLATFORMER_INPUTSYSTEM_H

#include <SDL2/SDL.h>
#include <string>


class InputSystem {
public:
    InputSystem();
    void update(bool& quit);

private:
    std::unordered_map<SDL_Scancode, std::string> keyboardMap;
    std::unordered_map<SDL_GameControllerButton, std::string> controllerMap;
    float deadZone = 0.3f;
    std::map<SDL_Scancode, bool> keyStates;
    std::map<SDL_Scancode, bool> justPressed;
    std::map<SDL_Scancode, bool> justReleased;
    std::pair<float, float> joystickDirection;

    void loadInputMaps();
    void loadControllerMap(const std::string& filepath);
    void loadScancodeMap(const std::string& filepath);
    void handleKeyboardInput(SDL_Event& e);
    void handleControllerInput(SDL_Event& e);
    void handleJoystickInput(SDL_Event& e);
    static SDL_Scancode mapControllerButtonToScancode(Uint8 button);
};


#endif //COOKIECUTTER_PLATFORMER_INPUTSYSTEM_H
