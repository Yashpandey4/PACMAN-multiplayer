/**
 * First State in the game, demonstrates start of the game play
 */

#include "GamePlay.h"
#include "LoadSprites.h"
#include "Maze.h"
#include "SFML/Graphics.hpp"

using namespace sf;

/**
 * Initialises the play state of the game
 */
void GamePlay::init() {
    logger = new Logger("GamePlay");
    maze = new Maze();
    logger->log("Playing State Initialised");
}

/**
 * Specifies actions which keep the play state of the game running in a loop
 */
void GamePlay::loop() {}

/**
 * Render sprites and stuff on the game window
 * @param window - Game Window
 */
void GamePlay::render(RenderWindow *window) {
    for (int i = 0; i < Maze::SizeX; i++)
    {
        for (int j = 0; j < Maze::SizeY; j++)
        {
            LoadSprites::mazePieces[maze->getTileCode(i, j)]->setPosition(i * 16.0f, j * 16.0f);
            window->draw(*LoadSprites::mazePieces[maze->getTileCode(i, j)]);
        }
    }

    Sprite pacManSprite;
    Sprite redGhostSprite;
    Sprite pinkGhostSprite;
    Sprite blueGhostSprite;
    Sprite orangeGhostSprite;

    pacManSprite = *LoadSprites::spritesMap.at(LoadSprites::PAC_MAN);
    redGhostSprite = *LoadSprites::spritesMap.at(LoadSprites::RED_GHOST);
    pinkGhostSprite = *LoadSprites::spritesMap.at(LoadSprites::PINK_GHOST);
    blueGhostSprite = *LoadSprites::spritesMap.at(LoadSprites::BLUE_GHOST);
    orangeGhostSprite = *LoadSprites::spritesMap.at(LoadSprites::ORANGE_GHOST);

    pacManSprite.setPosition(224,424);
    redGhostSprite.setPosition(224, 323);
    pinkGhostSprite.setPosition(224,280);
    blueGhostSprite.setPosition(192,280);
    orangeGhostSprite.setPosition(256,280);

    window->draw(pacManSprite);
    window->draw(redGhostSprite);
    window->draw(pinkGhostSprite);
    window->draw(blueGhostSprite);
    window->draw(orangeGhostSprite);
}

/**
 * Set action for key presses during gameplay
 * @param code - key code
 */
void GamePlay::keyPressed(int code) {
    logger->log("Key Pressed: "+to_string(code));
}

/**
 * Set action for key release during gameplay
 * @param code - key code
 */
void GamePlay::keyReleased(int code) {}