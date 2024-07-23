cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")

project(cookiecutter-platformer)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(SOURCE_FILES
        src/ConfigManager.cpp
        src/ConfigManager.h
        src/GameEngine.cpp
        src/GameEngine.h
)
add_library(cookiecutter-lib ${SOURCE_FILES})

add_executable(cookiecutter-platformer src/main.cpp)

target_link_libraries(cookiecutter-lib PUBLIC 
  SDL2::SDL2-static 
  SDL2_image::SDL2_image-static 
  SDL2_ttf::SDL2_ttf-static
  SDL2_mixer::SDL2_mixer-static
  nlohmann_json::nlohmann_json
)

target_link_libraries(cookiecutter-platformer PRIVATE cookiecutter-lib)
