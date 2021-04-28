/**
 * First State in the game, demonstrates start of the game play
 */

#include "GamePlay.h"
#include "LoadSprites.h"
#include "Maze.h"
#include "SFML/Graphics.hpp"

using namespace sf;

void GamePlay::init() {
    logger = new Logger("GamePlay");
    maze = new Maze();
    logger->log("Playing State Initialised");
}

void GamePlay::loop() {}

void GamePlay::render(RenderWindow *window) {
    for (int i = 0; i < Maze::SizeX; i++)
    {
        for (int j = 0; j < Maze::SizeY; j++)
        {
            LoadSprites::mazePieces[maze->getTileCode(i, j)]->setPosition(i * 16.0f, j * 16.0f);
            window->draw(*LoadSprites::mazePieces[maze->getTileCode(i, j)]);
        }
    }
//    CircleShape circle(200);
//    circle.setFillColor(Color::Blue);
//    window->draw(circle);
}

void GamePlay::keyPressed(int code) {
    logger->log("Key Pressed: "+to_string(code));
}

void GamePlay::keyReleased(int code) {}