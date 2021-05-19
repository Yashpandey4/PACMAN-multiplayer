//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_STATE_H
#define PACMAN_2PLAYER_STATE_H

#include "SFML/Graphics.hpp"

class StateServer {
public:
    virtual void init() {}
    virtual void loop() = 0;
    //virtual void render(sf::RenderWindow* window, int id) = 0;
    //virtual void keyPressed(int code) = 0;
    //virtual void keyReleased(int code) = 0;
};

#endif //PACMAN_2PLAYER_STATE_H
