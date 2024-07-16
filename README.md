# Order of Operations

1. Create default ```main.cpp``` file that includes the libs you need to build:
```cpp
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <nlohmann/json.hpp>

int main()
{
  SDL_Rect r = {0,0,10,10};
  std::cout << r.w << std::endl;  
  return r.x;
}

```

2. Create default ```CMakeLists.txt``` file that links the libs you need to build:
```CMake
cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "./vcpkg/scripts/buildsystems/vcpkg.cmake")

project(sdl_speedrun)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(sdl_speedrun main.cpp)

target_link_libraries(sdl_speedrun PRIVATE 
  SDL2::SDL2-static 
  SDL2_image::SDL2_image-static 
  SDL2_ttf::SDL2_ttf-static
  nlohmann_json::nlohmann_json
)
```

3. Create ```build.sh``` file that installs ```vcpkg``` if necessary:
```shell
#!/bin/bash

if [ ! -d "./vcpkg" ] ; then
  # shallow clone vcpkg repo
  git clone --depth 1 "https://github.com/microsoft/vcpkg.git"

  # bootstrap vcpkg install
  ./vcpkg/bootstrap-vcpkg.sh

  # remove vcpkg .git directory
  rm -rf ./vcpkg/.git

  # install project dependencies from vcpkg.json file in project root
  #  ./vcpkg/vcpkg install

# if the user already has vcpkg
else
  echo "vcpkg already exists"
  echo "using existing vcpkg"
  
# install project dependencies from vcpkg.json file in project root
  #  ./vcpkg/vcpkg install
fi
```

4. Make the build script executable and run it:
```bash
chmod +x build.sh
./build.sh
```

4. Initialize vcpkg project and create manifest file (```vcpkg.json```) via:
```bash
./vcpkg/vcpkg new --application
```

5. Add libs to manifest file via:
```bash
vcpkg add port <lib>
```

6. Make ```build``` dir and cd into it:
```bash
mkdir build && cd build
```

7. Run cmake to create build files via:
```bash
cmake ..    
``` 

8. Make executable via ``make```:
```bash
make
```

9. Run the executable via:
```bash
./sdl-speedrun
``` 





?. Set ```VCPKG_ROOT``` environment variabel:
```BASH
export VCPKG_ROOT=/path/to/vcpkg
export PATH=$VCPKG_ROOT:$PATH
```
