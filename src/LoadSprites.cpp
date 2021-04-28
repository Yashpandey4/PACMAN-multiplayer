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
            index++;
        }
    }

    logger.log("Sprites Ready");
}
