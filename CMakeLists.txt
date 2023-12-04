cmake_minimum_required(VERSION 3.23)
project(Snake)

set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
add_executable(Snake main.cpp Snake.cpp Snake.hpp Game.cpp Game.hpp GameState.cpp GameState.hpp Level.cpp Level.hpp AssetManager.cpp AssetManager.hpp)
target_link_libraries(Snake sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
