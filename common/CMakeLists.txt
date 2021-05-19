add_library(pacman-common 
    src/Netcommands.cpp
)   

target_include_directories(pacman-common PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
