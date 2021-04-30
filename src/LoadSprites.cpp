/**
 * This file loads and renders spriteFile for the gameplay
 */
#include "LoadSprites.h"

using namespace sf;

Texture LoadSprites::spriteFile;
Texture LoadSprites::maze;
Logger LoadSprites::logger("LoadSprites");
std::map<int, sf::Sprite*>  LoadSprites::spritesMap;
std::map<int, Animation> LoadSprites::animations;
sf::Sprite* LoadSprites::mazePieces[32];

// PacMan Movements
const int LoadSprites::PAC_MAN = 0;
const int LoadSprites::PAC_MAN_DOWN = 1;
const int LoadSprites::PAC_MAN_LEFT = 2;
const int LoadSprites::PAC_MAN_RIGHT = 3;

// Blinky Movements
const int LoadSprites::RED_GHOST = 4;
const int LoadSprites::RED_GHOST_DOWN = 5;
const int LoadSprites::RED_GHOST_LEFT = 6;
const int LoadSprites::RED_GHOST_RIGHT = 7;

// Pinky Movements
const int LoadSprites::PINK_GHOST = 8;
const int LoadSprites::PINK_GHOST_DOWN = 9;
const int LoadSprites::PINK_GHOST_LEFT = 10;
const int LoadSprites::PINK_GHOST_RIGHT = 11;

// Inky Movements
const int LoadSprites::BLUE_GHOST = 12;
const int LoadSprites::BLUE_GHOST_DOWN = 13;
const int LoadSprites::BLUE_GHOST_LEFT = 14;
const int LoadSprites::BLUE_GHOST_RIGHT = 15;

// Clyde Movements
const int LoadSprites::ORANGE_GHOST = 16;
const int LoadSprites::ORANGE_GHOST_DOWN = 17;
const int LoadSprites::ORANGE_GHOST_LEFT = 18;
const int LoadSprites::ORANGE_GHOST_RIGHT = 19;

// Misc
const int LoadSprites::FRIGHTENED_GHOST = 20;
const int LoadSprites::DEAD_PAC_MAN = 21;

/**
 * This is the main function which loads all the sprites, including characters and mazes
 */
void LoadSprites::load() {

    maze.loadFromFile("assets/maze.png");
    int index = 0;
    for(int i=0; i<8; i++) {
        for(int j=0; j<4;j++) {
            mazePieces[index] = new sf::Sprite(maze, sf::IntRect(i*8,j*8,8,8));
            mazePieces[index]->setScale(2.0f, 2.0f);
            index++;
        }
    }

    spriteFile.loadFromFile("assets/characters.png");

    loadSpriteFromFile(LoadSprites::PAC_MAN, 0, 0, 3);
    loadSpriteFromFile(LoadSprites::PAC_MAN_DOWN, 45, 0, 3);
    loadSpriteFromFile(LoadSprites::PAC_MAN_LEFT, 90, 0, 3);
    loadSpriteFromFile(LoadSprites::PAC_MAN_RIGHT, 135, 0, 3);

    loadSpriteFromFile(LoadSprites::RED_GHOST, 0, 15, 2);
    loadSpriteFromFile(LoadSprites::RED_GHOST_DOWN, 30, 15, 2);
    loadSpriteFromFile(LoadSprites::RED_GHOST_LEFT, 60, 15, 2);
    loadSpriteFromFile(LoadSprites::RED_GHOST_RIGHT, 90, 15, 2);

    loadSpriteFromFile(LoadSprites::PINK_GHOST, 0, 30, 2);
    loadSpriteFromFile(LoadSprites::PINK_GHOST_DOWN, 30, 30, 2);
    loadSpriteFromFile(LoadSprites::PINK_GHOST_LEFT, 60, 30, 2);
    loadSpriteFromFile(LoadSprites::PINK_GHOST_RIGHT, 90, 30, 2);

    loadSpriteFromFile(LoadSprites::BLUE_GHOST, 0, 45, 2);
    loadSpriteFromFile(LoadSprites::BLUE_GHOST_DOWN, 30, 45, 2);
    loadSpriteFromFile(LoadSprites::BLUE_GHOST_LEFT, 60, 45, 2);
    loadSpriteFromFile(LoadSprites::BLUE_GHOST_RIGHT, 90, 45, 2);

    loadSpriteFromFile(LoadSprites::ORANGE_GHOST, 0, 60, 2);
    loadSpriteFromFile(LoadSprites::ORANGE_GHOST_DOWN, 30, 60, 2);
    loadSpriteFromFile(LoadSprites::ORANGE_GHOST_LEFT, 60, 60, 2);
    loadSpriteFromFile(LoadSprites::ORANGE_GHOST_RIGHT, 90, 60, 2);

    loadSpriteFromFile(LoadSprites::FRIGHTENED_GHOST, 120, 15, 2);
    loadSpriteFromFile(LoadSprites::DEAD_PAC_MAN, 0, 75, 12);

    logger.log("Sprites Ready");
}

/**
 * This functions cuts the sprite sheet to load a specific sprite from the same
 * @param key : Map key of the sprite character
 * @param rectLeft : The left offset of the bounding box of sprite
 * @param rectTop : The top offset of the bounding box of sprite
 * @param animationFrames: Frames animating the moving sprite
 */
void LoadSprites::loadSpriteFromFile(int key, int rectLeft, int rectTop, int animationFrames) {
    sf::IntRect * rectangle = new sf::IntRect(rectLeft, rectTop, 15, 15);
    Sprite* sprite = new sf::Sprite(spriteFile, *rectangle);
    sprite->setScale(2.0f, 2.0f);
    sprite->setOrigin(7.5f, 7.5f);
    spritesMap.insert(std::pair<int, sf::Sprite*>(key, sprite));
    animations.insert(std::pair<int, Animation>(key, Animation(rectangle, animationFrames)));
}
