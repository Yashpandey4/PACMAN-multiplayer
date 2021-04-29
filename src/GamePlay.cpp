/**
 * First State in the game, demonstrates start of the game play
 */

#include "PacMan.h"
#include "Ghost.h"
#include "GamePlay.h"
#include "Direction.h"
#include "LoadSprites.h"
#include "Maze.h"
#include "SFML/Graphics.hpp"

#include <cmath>

using namespace sf;

/**
 * Initialises the play state of the game
 */
void GamePlay::init() {
    logger = new Logger("GamePlay");
    maze = new Maze();
    pacMan = new PacMan();
    redGhost = new Ghost(13,14,3,4);
    pinkGhost = new Ghost(13,17,23,4);
    blueGhost = new Ghost(11,17,26,32);
    orangeGhost = new Ghost(15,17,1,32);
    logger->log("Playing State Initialised");
}

/**
 * Specifies actions which keep the play state of the game running in a loop
 */
void GamePlay::loop() {
    if(isPacManMovementAllowed())
        pacMan->movePacman();
    else
        pacMan->stopPacman();

    if (maze->isMazeIntersection(pacMan->getCellX(), pacMan->getCellY()))
        pacMan->stopPacman();

    maze->removePellets(pacMan);

    redGhost->setGhostDestination(pacMan->getCellX(), pacMan->getCellY());
    pinkGhost->setGhostDestination(pacMan->getCellX(), pacMan->getCellY());
    blueGhost->setGhostDestination(pacMan->getCellX(), pacMan->getCellY());
    orangeGhost->setGhostDestination(pacMan->getCellX(), pacMan->getCellY());

    handleGhostMovement(redGhost);
    handleGhostMovement(pinkGhost);
    handleGhostMovement(blueGhost);
    handleGhostMovement(orangeGhost);
}

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
    // logger->log("Key Pressed: "+to_string(code));
    switch (code) {
        case Keyboard::Up:
            pacMan->queueDirection(Direction::UP);
            break;
        case Keyboard::Down:
            pacMan->queueDirection(Direction::DOWN);
            break;
        case Keyboard::Left:
            pacMan->queueDirection(Direction::LEFT);
            break;
        case Keyboard::Right:
            pacMan->queueDirection(Direction::RIGHT);
            break;
    }
}

/**
 * Set action for key release during gameplay
 * @param code - key code
 */
void GamePlay::keyReleased(int code) {}

/**
 * Determines if the PacMan character is free to move
 * @return True if pacman can move, false otherwise
 */
bool GamePlay::isPacManMovementAllowed() {
    if (!pacMan->getDirections().empty()) {
        switch (pacMan->getDirections().front()) {
            case Direction::UP:
                return !maze->isCellBlockingCharacter(pacMan->getCellX(), pacMan->getCellY() - 1);
                break;
            case Direction::DOWN:
                return !maze->isCellBlockingCharacter(pacMan->getCellX(), pacMan->getCellY() + 1);
                break;
            case Direction::LEFT:
                return !maze->isCellBlockingCharacter(pacMan->getCellX() - 1, pacMan->getCellY());
                break;
            case Direction::RIGHT:
                return !maze->isCellBlockingCharacter(pacMan->getCellX() + 1, pacMan->getCellY());
                break;
        }
    }
    return true;
}

/**
 * Calculates the distance between ghost position and the x,y coordinates supplied to it
 * @param ghost - Ghost for which distance is being calculated
 * @param x - target X
 * @param y - target Y
 * @return distance
 */
float GamePlay::calculateGhostDistance(Ghost *ghost, int x, int y) {
    float distance = 1000000.0f;
    if (maze->isMazeIntersection(ghost->getCellX(), ghost->getCellY())) {
        if (!maze->isCellBlockingCharacter(ghost->getCellX() + x, ghost->getCellY() + y)) {
            // ((x2-x1)^2 - (Y2-Y1)^2)^(1/2)
            distance = (float) sqrt(pow((ghost->getDestinationX() - (ghost->getCellX() + x)), 2) + pow((ghost->getDestinationY() - (ghost->getCellY() + y)), 2));
        }
    }
    return distance;
}

/**
 *
 * @param ghost
 */
void GamePlay::handleGhostMovement(Ghost *ghost) {
    if(maze->isMazeIntersection(ghost->getCellX(), ghost->getCellY())) {
        float distanceRight = calculateGhostDistance(ghost, 1, 0);
        float distanceLeft = calculateGhostDistance(ghost, -1, 0);
        float distanceUp = calculateGhostDistance(ghost, 0, -1);
        float distanceDown = calculateGhostDistance(ghost, 0, 1);

        if (distanceRight < distanceLeft && distanceRight < distanceUp && distanceRight < distanceDown)
            ghost->setDirection(Direction::RIGHT);
        else if (distanceLeft < distanceRight && distanceLeft < distanceUp && distanceLeft < distanceDown)
            ghost->setDirection(Direction::LEFT);
        else if (distanceUp < distanceLeft && distanceUp < distanceRight && distanceUp < distanceDown)
            ghost->setDirection(Direction::UP);
        else if (distanceDown < distanceLeft && distanceDown < distanceUp && distanceDown < distanceRight)
            ghost->setDirection(Direction::DOWN);
    }
    if (isGhostMovementAllowed(ghost))
        ghost->moveGhost();
}

/**
 *
 * @param ghost
 * @return
 */
bool GamePlay::isGhostMovementAllowed(Ghost *ghost) {
    switch (ghost->getDirection()) {
        case Direction::UP:
            return !maze->isCellBlockingCharacter(ghost->getCellX(), ghost->getCellY() - 1);
            break;
        case Direction::DOWN:
            return !maze->isCellBlockingCharacter(ghost->getCellX(), ghost->getCellY() + 1);
            break;
        case Direction::LEFT:
            return !maze->isCellBlockingCharacter(ghost->getCellX() - 1, ghost->getCellY());
            break;
        case Direction::RIGHT:
            return !maze->isCellBlockingCharacter(ghost->getCellX() + 1, ghost->getCellY());
            break;
        default:
            return false;
    }
}


