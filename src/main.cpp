#include <iostream>

#include "ConfigManager.h"
#include "GameEngine.h"


int main()
{
    try {
        ConfigManager& config = ConfigManager::getInstance();
        config.loadConfig("etc/run_config.json");

        GameEngine gameEngine;
        gameEngine.run();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

