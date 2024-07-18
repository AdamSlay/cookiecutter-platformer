#include <fstream>
#include <iostream>
#include <unistd.h>

#include "ConfigManager.h"


ConfigManager& ConfigManager::getInstance() {
    static ConfigManager instance;
    return instance;
}

void ConfigManager::loadConfig(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file){
        std::cerr << "Unable to open Config file: " << filePath << std::endl;

        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            std::cerr << "Current working dir: " << cwd << std::endl;
        }
        return;
    }
    if (file.is_open()) {
        file >> config;
    }
}

int ConfigManager::getWindowWidth() const {
    return config["window"]["width"];
}

int ConfigManager::getWindowHeight() const {
    return config["window"]["height"];
}

int ConfigManager::getFontSize() const {
    return config["font"]["size"];
}

std::string ConfigManager::getFontPath() const {
    return config["font"]["path"];
}
