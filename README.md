This is a cookiecutter 2D platformer video game project template. It is intended to be used for game jams, prototyping,
or as a starting point for a full game project. This project is written entirely in C++ and uses the [SDL2](https://www.libsdl.org/) 
library for interacting with hardware and [vcpkg](https://vcpkg.io/en/) for managing dependencies. The project uses an 
Entity-Component-System (ECS) architecture for game object management and a simple state machine for game state management.

## Installation
After cloning the repository, you need to make the build script executable and run it to build the project: 
```bash
chmod +x build.sh
./build.sh
```
The script will install the necessary dependencies using vcpkg and then build the project using CMake. 
The script will create a ```build``` directory and place the compiled executable in that directory. You can run the 
executable from the command line to start the game using the following command while in the project root directory:
```bash
./build/cookiecutter-platformer
```