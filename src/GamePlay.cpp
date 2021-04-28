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
    pacMan = new Character(13,26);
    redGhost = new Character(13,14);
    pinkGhost = new Character(13,17);
    blueGhost = new Character(11,17);
    orangeGhost = new Character(15,17);
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
    for (int i = 0; i < Maze::SIZE_X; i++)
    {
        for (int j = 0; j < Maze::SIZE_Y; j++)
        {
            LoadSprites::mazePieces[maze->getCellCode(i, j)]->setPosition(i * 16.0f, j * 16.0f);
            window->draw(*LoadSprites::mazePieces[maze->getCellCode(i, j)]);
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

    pacManSprite.setPosition(pacMan->getScreenPositionX(),pacMan->getScreenPositionY());
    redGhostSprite.setPosition(redGhost->getScreenPositionX(), redGhost->getScreenPositionY());
    pinkGhostSprite.setPosition(pinkGhost->getScreenPositionX(),pinkGhost->getScreenPositionY());
    blueGhostSprite.setPosition(blueGhost->getScreenPositionX(),blueGhost->getScreenPositionY());
    orangeGhostSprite.setPosition(orangeGhost->getScreenPositionX(),orangeGhost->getScreenPositionY());

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