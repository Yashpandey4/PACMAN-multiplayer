/**
 * This file loads and renders spriteFile for the gameplay
 */
#include "LoadSprites.h"

using namespace sf;

Texture LoadSprites::spriteFile;
Texture LoadSprites::maze;
Logger LoadSprites::logger("LoadSprites");

sf::Sprite* LoadSprites::mazePieces[32];

void LoadSprites::load() {

    maze.loadFromFile("assets/maze.png");
    int index = 0;
    for(int i=0; i<8; i++) {
        for(int j=0; j<4;j++) {
            mazePieces[index] = new sf::Sprite(maze, sf::IntRect(i*8,j*8,8,8));
            mazePieces[index]->setScale(2.0f, 2.0f);
        }
    }

//    spriteFile.loadFromFile("../assets/characters.png");
//
//    sf::Sprite* pacMan = new sf::Sprite(spriteFile, sf::IntRect(0,0,15,15));
//    pacMan->setScale(2.0f, 2.0f);
//    pacMan->setOrigin(7.5f, 7.5f);

    logger.log("Sprites Ready");
}
