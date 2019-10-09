cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(DinoDiamond src/components/state/state.cpp src/main.cpp src/components/game/game.cpp src/components/controller/controller.cpp src/components/renderer/renderer.cpp src/components/parallax/parallax.cpp src/components/player/player.cpp src/components/challenges/challenge.cpp src/components/challenges/diamonds/diamond.cpp src/components/challenges/fires/fire.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(DinoDiamond ${SDL2_LIBRARIES} SDL2_image SDL2_mixer)
