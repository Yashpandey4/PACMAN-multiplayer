//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_LOADSPRITES_H
#define PACMAN_2PLAYER_LOADSPRITES_H

#include "SFML/Graphics.hpp"
#include "Logger.h"

class LoadSprites {
private:
    static sf::Texture spriteFile;
    static sf::Texture maze;
    static Logger logger;

    // static std::map<int, sf::Sprite*> sprites;
    // static std::map<int, Animation> animations;

public:
    static void load();
    static sf::Sprite* mazePieces[];
};


#endif //PACMAN_2PLAYER_LOADSPRITES_H
