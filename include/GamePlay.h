//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_GAMEPLAY_H
#define PACMAN_2PLAYER_GAMEPLAY_H

#include "State.h"
#include "Logger.h"

class GamePlay : public State {
private:
    Logger* logger;

public:
    void init();
    void loop();
    void render(sf::RenderWindow* window);
    void keyPressed(int code);
    void keyReleased(int code);
};


#endif //PACMAN_2PLAYER_GAMEPLAY_H
