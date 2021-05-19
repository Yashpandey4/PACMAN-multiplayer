cmake_minimum_required(VERSION 3.15)
project(PACMAN_2Player)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system")

include_directories(include)
add_executable(PACMAN_2Player src/GameWindow.cpp src/Main.cpp include/GameWindow.h include/Logger.h src/Logger.cpp src/State.cpp include/State.h src/StateMachine.cpp include/StateMachine.h src/GamePlay.cpp include/GamePlay.h src/LoadSprites.cpp include/LoadSprites.h src/Maze.cpp include/Maze.h src/Character.cpp include/Character.h src/PacMan.cpp include/PacMan.h include/Direction.h)

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

target_link_libraries (PACMAN_2Player sfml-graphics sfml-window sfml-system)