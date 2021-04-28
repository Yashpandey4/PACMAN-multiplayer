/**
 * This file loads and renders spriteFile for the gameplay
 */
#include "LoadSprites.h"

using namespace sf;

Texture LoadSprites::spriteFile;
Texture LoadSprites::maze;
Logger LoadSprites::logger("LoadSprites");
std::map<int, sf::Sprite*>  LoadSprites::spritesMap;
sf::Sprite* LoadSprites::mazePieces[32];

// PacMan Movements
const int LoadSprites::PAC_MAN = 0;

// Blinky Movements
const int LoadSprites::RED_GHOST = 1;

// Pinky Movements
const int LoadSprites::PINK_GHOST = 2;

// Inky Movements
const int LoadSprites::BLUE_GHOST = 3;

// Clyde Movements
const int LoadSprites::ORANGE_GHOST = 4;

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

    loadSpriteFromFile(LoadSprites::PAC_MAN, 0, 0);

    loadSpriteFromFile(LoadSprites::RED_GHOST, 0, 15);
    loadSpriteFromFile(LoadSprites::PINK_GHOST, 0, 30);
    loadSpriteFromFile(LoadSprites::BLUE_GHOST, 0, 45);
    loadSpriteFromFile(LoadSprites::ORANGE_GHOST, 0, 60);


    logger.log("Sprites Ready");
}

/**
 * This functions cuts the sprite sheet to load a specific sprite from the same
 * @param key : Map key of the sprite character
 * @param rectLeft : The left offset of the bounding box of sprite
 * @param rectTop : The top offset of the bounding box of sprite
 */
void LoadSprites::loadSpriteFromFile(int key, int rectLeft, int rectTop) {
    Sprite* sprite = new sf::Sprite(spriteFile, sf::IntRect(rectLeft, rectTop, 15, 15));
    sprite->setScale(2.0f, 2.0f);
    sprite->setOrigin(7.5f, 7.5f);
    spritesMap.insert(std::pair<int, sf::Sprite*>(key, sprite));
}
