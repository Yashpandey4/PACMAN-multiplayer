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
    // static std::map<int, Animation> animations;
    static sf::Texture maze;
    static Logger logger;
    static void loadSpriteFromFile(int key, int rectLeft, int rectTop);

public:
    static void load();
    static sf::Sprite* mazePieces[];
    static std::map<int, sf::Sprite*> spritesMap;

    static const int PAC_MAN;
    static const int BLUE_GHOST;
    static const int ORANGE_GHOST;
    static const int PINK_GHOST;
    static const int RED_GHOST;
};


#endif //PACMAN_2PLAYER_LOADSPRITES_H
