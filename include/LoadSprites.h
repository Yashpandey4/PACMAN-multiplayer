//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_LOADSPRITES_H
#define PACMAN_2PLAYER_LOADSPRITES_H

#include "SFML/Graphics.hpp"
#include "Logger.h"
#include "Animation.h"
#include "Direction.h"

class LoadSprites {
private:
    static sf::Texture spriteFile;
    static std::map<int, sf::Sprite*> spritesMap;
    static std::map<int, Animation> animations;
    static sf::Texture maze;
    static Logger logger;
    static void loadSpriteFromFile(int key, int rectLeft, int rectTop, int animationFrames);

public:
    static void load();

    static sf::Sprite* mazePieces[];
    static sf::Sprite* mazePieces_temp[];

    static sf::Sprite* get(int value, bool animated, Direction facing);
};


#endif //PACMAN_2PLAYER_LOADSPRITES_H
