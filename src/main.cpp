#include <iostream>

#include "ConfigManager.h"
#include "GameEngine.h"


int main()
{
    ConfigManager& config = ConfigManager::getInstance();
    config.loadConfig("etc/run_config.json");

    try {
        GameEngine gameEngine;
        gameEngine.run();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

