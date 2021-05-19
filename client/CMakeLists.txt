include_directories(include)

add_executable(${PROJECT_NAME} 
    
    src/GameWindow.cpp src/Main.cpp src/Logger.cpp src/StateMachine.cpp src/GamePlay.cpp src/LoadSprites.cpp src/Maze.cpp src/Character.cpp src/PacMan.cpp src/Ghost.cpp src/Animation.cpp src/AudioManager.cpp src/Client.cpp
        
)
setup_target_compile(${PROJECT_NAME})
#Finally
target_link_libraries(${PROJECT_NAME}
    pacman-common
    pacman-server
    Threads::Threads 
    ${SFML_LIBRARIES} 
    ${SFML_DEPENDENCIES}
)

