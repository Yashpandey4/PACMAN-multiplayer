cmake_minimum_required(VERSION 3.15)
project(PACMAN_2Player)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system")

include_directories(include)
add_executable(
        PACMAN_2Player
        src/GameWindow.cpp src/Main.cpp src/Logger.cpp src/StateMachine.cpp src/GamePlay.cpp src/LoadSprites.cpp src/Maze.cpp src/Character.cpp src/PacMan.cpp src/Ghost.cpp src/Animation.cpp src/AudioManager.cpp
        include/GameWindow.h include/Logger.h include/State.h include/StateMachine.h include/GamePlay.h include/LoadSprites.h include/Maze.h include/Character.h include/PacMan.h include/Direction.h include/Ghost.h include/Animation.h include/Entity.h include/Audio.h include/AudioManager.h
)

set(SFML_INCLUDE_DIR "include/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "include/SFML-2.5.1/lib")
set(SFML_DIR "include/SFML-2.5.1/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

target_link_libraries (PACMAN_2Player sfml-graphics sfml-window sfml-system sfml-network sfml-audio)