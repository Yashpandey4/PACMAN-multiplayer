add_library(pacman-server
    src/CharacterServer.cpp
    src/GhostServer.cpp
    src/MazeServer.cpp
    src/PacManServer.cpp
    src/Server.cpp
)

target_include_directories(pacman-server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
