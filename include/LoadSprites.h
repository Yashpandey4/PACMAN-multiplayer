//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_LOADSPRITES_H
#define PACMAN_2PLAYER_LOADSPRITES_H

#include "SFML/Graphics.hpp"
#include "Logger.h"
#include "Animation.h"

class LoadSprites {
private:
    static sf::Texture spriteFile;
    static std::map<int, Animation> animations;
    static sf::Texture maze;
    static Logger logger;
    static void loadSpriteFromFile(int key, int rectLeft, int rectTop, int animationFrames);

    static const int PAC_MAN_DOWN;
    static const int PAC_MAN_LEFT;
    static const int PAC_MAN_RIGHT;

    static const int RED_GHOST_DOWN;
    static const int RED_GHOST_LEFT;
    static const int RED_GHOST_RIGHT;

    static const int PINK_GHOST_DOWN;
    static const int PINK_GHOST_LEFT;
    static const int PINK_GHOST_RIGHT;

    static const int BLUE_GHOST_DOWN;
    static const int BLUE_GHOST_LEFT;
    static const int BLUE_GHOST_RIGHT;

    static const int ORANGE_GHOST_DOWN;
    static const int ORANGE_GHOST_LEFT;
    static const int ORANGE_GHOST_RIGHT;

public:
    static void load();
    static sf::Sprite* mazePieces[];
    static std::map<int, sf::Sprite*> spritesMap;

    static const int PAC_MAN;

    static const int BLUE_GHOST;
    static const int ORANGE_GHOST;
    static const int PINK_GHOST;
    static const int RED_GHOST;

    static const int FRIGHTENED_GHOST;
    static const int DEAD_PAC_MAN;
};


#endif //PACMAN_2PLAYER_LOADSPRITES_H
