cmake_minimum_required(VERSION 3.24)
project(GameProject)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -lcrt0")
add_executable(GameProject main.cpp sector.cpp sector.h gameData.cpp gameData.h gameEngine.cpp gameEngine.h rectButton.h switchButton.h)

include_directories("/opt/homebrew/Cellar/raylib/4.5.0/include")
include_directories("/opt/raylib-cpp/include")
target_link_libraries(GameProject "/opt/homebrew/Cellar/raylib/4.5.0/lib/libraylib.dylib")
