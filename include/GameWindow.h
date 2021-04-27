//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_GAMEWINDOW_H
#define PACMAN_2PLAYER_GAMEWINDOW_H

#include "SFML/Graphics.hpp"
#include "Logger.h"
#include "StateMachine.h"

using namespace sf;

class GameWindow
{
private:
    static RenderWindow window;
    static Logger logger;
    static StateMachine stateMachine;

public:
    static void init();
    static bool isRunning();
    static void handleEvents();
    static void render();
};

#endif //PACMAN_2PLAYER_GAMEWINDOW_H
