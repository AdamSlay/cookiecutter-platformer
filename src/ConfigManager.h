#ifndef COOKIECUTTER_PLATFORMER_CONFIGMANAGER_H
#define COOKIECUTTER_PLATFORMER_CONFIGMANAGER_H

#pragma once
#include <nlohmann/json.hpp>
#include <string>

class ConfigManager {
public:
    static ConfigManager& getInstance();

    void loadConfig(const std::string& filePath);

    int getWindowWidth() const;
    int getWindowHeight() const;
    std::string getWindowTitle() const;
    int getFontSize() const;
    std::string getFontPath() const;

private:
    ConfigManager() = default;

    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    nlohmann::json config;
};

#endif //COOKIECUTTER_PLATFORMER_CONFIGMANAGER_H
