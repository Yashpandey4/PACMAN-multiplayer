/**
 * First State in the game, demonstrates start of the game play
 */

#include "PacMan.h"
#include "Ghost.h"
#include "GamePlay.h"
#include "Direction.h"
#include "LoadSprites.h"
#include "Maze.h"
#include "Audio.h"

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include <cmath>
#include <Entity.h>

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

    redGhost->teleport(13, 14);

    audioManager = new AudioManager();
    stopSirenAndLoop(Sounds::GameStart, false, VOLUME);

    waitTime = 0;
}

/**
 * Specifies actions which keep the play state of the game running in a loop
 */
void GamePlay::loop() {
    // a hacky way to freeze game when intro music is playing - give player some time to prepare.
    while(audioManager->isPlayingAudio(Sounds::GameStart) || audioManager->isPlayingAudio(Sounds::Death)) {
        continue;
    }

    if(isPacManMovementAllowed() && !pacMan->isPacmanDead())
        pacMan->movePacman();
    else
        pacMan->stopPacman();

    if (maze->isMazeIntersection(pacMan->getCellX(), pacMan->getCellY()))
        pacMan->stopPacman();

    removePellets();

    setChaseBehaviour();

    handleGhostMovement(redGhost);
    handleGhostMovement(pinkGhost);
    handleGhostMovement(blueGhost);
    handleGhostMovement(orangeGhost);

    if(pacMan->getPelletsEaten() == 5)
        pinkGhost->teleport(13, 14);
    if(pacMan->getPelletsEaten() == 50)
        blueGhost->teleport(13, 14);
    if(pacMan->getPelletsEaten() == 100)
        orangeGhost->teleport(13, 14);

    teleportTunnels(pacMan);
    teleportTunnels(redGhost);
    teleportTunnels(pinkGhost);
    teleportTunnels(blueGhost);
    teleportTunnels(orangeGhost);

    handleGhostFrightening(redGhost);
    handleGhostFrightening(pinkGhost);
    handleGhostFrightening(blueGhost);
    handleGhostFrightening(orangeGhost);

    if (pacMan->getPelletsEaten() == 240) {
        redGhost->teleport(-2,-2);
        pinkGhost->teleport(-2,-2);
        blueGhost->teleport(-2,-2);
        orangeGhost->teleport(-2,-2);
        waitTime++;
    }

    if (pacMan->isPacmanDead())
        waitTime++;

    if (waitTime == 200) {
        if (pacMan->isPacmanDead()) {
            if (redGhost->isGhostOutOfCage())
                redGhost->teleport(13, 14);
            if (pinkGhost->isGhostOutOfCage())
                pinkGhost->teleport(13,14);
            if (blueGhost->isGhostOutOfCage())
                blueGhost->teleport(13,14);
            if (orangeGhost->isGhostOutOfCage())
                orangeGhost->teleport(13,14);
            pacMan->teleport(13,26);
            pacMan->setPacmanDead(false);
            waitTime = 0;
            logger->log("PacMan Dead. Resetting Game.");
            stopSirenAndLoop(Sounds::Death, false, VOLUME);
        }
        else {
            GamePlay::init();
            waitTime = 0;
        }
    }

}

/**
 * In “Chase” mode, the ghosts are trying to find and capture Pac-Man.
 * Each of the four ghosts has a unique behaviour while chasing Pac-Man.
 * This function defines this behaviour
 */
void GamePlay::setChaseBehaviour() {
    if (!pacMan->getDirections().empty()) {
        // Red Ghost Directly Chases Pacman
        // Blinky the red ghost is very aggressive in its approach while chasing Pac-Man and will follow Pac-Man once located.
        if (!redGhost->isScatterGhosts()) {
            redGhost->setGhostDestination(pacMan->getCellX(), pacMan->getCellY());
        }

        // Pink Ghost is off from PacMan's location by 4 cells (lurks around PacMan)
        // Pinky the pink ghost will attempt to ambush Pac-Man by trying to get in front of him and cut him off.
        if (!pinkGhost->isScatterGhosts()) {
            switch (pacMan->getDirections().front()) {
                case Direction::UP:
                    pinkGhost->setGhostDestination(pacMan->getCellX(), pacMan->getCellY() - 4);
                    break;
                case Direction::DOWN:
                    pinkGhost->setGhostDestination(pacMan->getCellX(), pacMan->getCellY() + 4);
                    break;
                case Direction::LEFT:
                    pinkGhost->setGhostDestination(pacMan->getCellX() - 4, pacMan->getCellY());
                    break;
                case Direction::RIGHT:
                    pinkGhost->setGhostDestination(pacMan->getCellX() + 4, pacMan->getCellY());
                    break;
            }
        }

        // Blue Ghost Patrols with direction close to Pacman decided by distance between the two
        // Inky the cyan ghost will patrol an area and is not very predictable in this mode.
        if (!blueGhost->isScatterGhosts()) {
            blueGhost->setGhostDestination(pacMan->getCellX() + (redGhost->getCellX() - pacMan->getCellX()), pacMan->getCellY() + (
                    redGhost->getCellY() - pacMan->getCellY()));
        }

        // Orange Ghost chases Pacman if it is close to clyde else it minds its own business.
        // Clyde the orange ghost is moving in a random fashion and seems to stay out of the way of Pac-Man.
        if (!orangeGhost->isScatterGhosts()) {
            if (sqrt(pow((orangeGhost->getCellX() - (pacMan->getCellX())), 2) + pow((orangeGhost->getCellY() - (pacMan->getCellY())), 2)) < 9) {
                orangeGhost->setGhostDestination(pacMan->getCellX(), pacMan->getCellY());
            }
            else {
                orangeGhost->setGhostDestination(1, 32);
            }
        }
    }
}

/**
 * Render sprites and stuff on the game window
 * @param window - Game Window
 */
void GamePlay::render(RenderWindow *window) {
    // Load Maze
    for (int i = 0; i < Maze::SIZE_X; i++)
    {
        for (int j = 0; j < Maze::SIZE_Y; j++)
        {
            LoadSprites::mazePieces[maze->getCellCode(i, j)]->setPosition(i * 16.0f, j * 16.0f);
            window->draw(*LoadSprites::mazePieces[maze->getCellCode(i, j)]);
        }
    }

    // Load Character Sprites and animate it
    Sprite pacManSprite;
    Sprite redGhostSprite;
    Sprite pinkGhostSprite;
    Sprite blueGhostSprite;
    Sprite orangeGhostSprite;

    if (pacMan->getDirections().empty())
        pacManSprite = *LoadSprites::get(Entity::PAC_MAN, false, Direction::UNSET);
    else
        pacManSprite = *LoadSprites::get(Entity::PAC_MAN, true, pacMan->getDirections().front());

    if (pacMan->isPacmanDead())
        pacManSprite = *LoadSprites::get(Entity::DEAD_PAC_MAN, true, Direction::UNSET);

    if (!redGhost->isGhostFrightened())
        redGhostSprite = *LoadSprites::get(Entity::RED_GHOST, redGhost->isGhostOutOfCage(), redGhost->getDirection());
    else
        redGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, redGhost->isGhostOutOfCage(), redGhost->getDirection());

    if (!pinkGhost->isGhostFrightened())
        pinkGhostSprite = *LoadSprites::get(Entity::PINK_GHOST, pinkGhost->isGhostOutOfCage(), pinkGhost->getDirection());
    else
        pinkGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, pinkGhost->isGhostOutOfCage(), pinkGhost->getDirection());

    if (!blueGhost->isGhostFrightened())
        blueGhostSprite = *LoadSprites::get(Entity::BLUE_GHOST, blueGhost->isGhostOutOfCage(), blueGhost->getDirection());
    else
        blueGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, blueGhost->isGhostOutOfCage(), blueGhost->getDirection());

    if (!orangeGhost->isGhostFrightened())
        orangeGhostSprite = *LoadSprites::get(Entity::ORANGE_GHOST, orangeGhost->isGhostOutOfCage(), orangeGhost->getDirection());
    else
        orangeGhostSprite = *LoadSprites::get(Entity::FRIGHTENED_GHOST, orangeGhost->isGhostOutOfCage(), orangeGhost->getDirection());

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
    if (!maze->isCellBlockingCharacter(ghost->getCellX() + x, ghost->getCellY() + y)) {
        // ((x2-x1)^2 - (Y2-Y1)^2)^(1/2)
        distance = (float) sqrt(pow((ghost->getDestinationX() - (ghost->getCellX() + x)), 2) + pow((ghost->getDestinationY() - (ghost->getCellY() + y)), 2));
    }
    return distance;
}

/**
 * This function determines the movement behaviour of the ghosts
 * @param ghost
 */
void GamePlay::handleGhostMovement(Ghost *ghost) {
    // Set Scattering to false if target tile reached
    if(ghost->isScatterGhosts()) {
        if(ghost->getCellX() == ghost->getDestinationX() && ghost->getCellY() == ghost->getDestinationY()) {
            ghost->setScatterGhosts(false);
        }
    }

    if(maze->isMazeIntersection(ghost->getCellX(), ghost->getCellY())) {
        if (ghost->isGhostDecision()) {
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
        ghost->setGhostDecision(false);
    }
    else {
        ghost->setGhostDecision(true);
    }

    if (isGhostMovementAllowed(ghost) && ghost->isGhostOutOfCage())
        ghost->moveGhost();
    else
        ghost->setGhostDecision(true);
}

/**
 * This function determines if ghost movement is allowed from a target to destination cell
 * @param ghost - Ghost in question (who we want to move)
 * @return Boolean, True if Movement is allowed
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

/**
 * @TODO: Automate tunnel locations in a random maze instead of hardcoding
 * This function helps the characters teleport from one end of the tunnel to the other
 * @param character
 */
void GamePlay::teleportTunnels(Character *character) {
    if (character->getCellX() == 0 && character->getCellY() == 17)
        character->teleport(26, 17);
    else if (character->getCellX() == 27 && character->getCellY() == 17)
        character->teleport(1, 17);
}

/**
 * Handles the frightened state of ghosts, when pacman eats power pellets
 * @param ghost - The frightened ghost in question
 */
void GamePlay::handleGhostFrightening(Ghost *ghost) {
     if (pacMan->getCellX() == ghost->getCellX() && pacMan->getCellY() == ghost->getCellY()) {
         if (ghost->isGhostFrightened()) {
             ghost->teleport(13, 14);
             ghost->setGhostFrightened(false);
         }
         else {
             pacMan->setPacmanDead(true);
             redGhost->teleport(-2, -2);
             pinkGhost->teleport(-2,-2);
             blueGhost->teleport(-2,-2);
             orangeGhost->teleport(-2,-2);
         }
     }
}


/**
 * Removes the pellets from the game screen when PacMan eats them
 */
void GamePlay::removePellets() {
    // Pellet Tile -> Blank Tile
    if(maze->cells[pacMan->getCellX()][pacMan->getCellY()] == 26) {
        maze->cells[pacMan->getCellX()][pacMan->getCellY()] = 30;
        pacMan->eatPellets();
        if(!audioManager->isPlayingAudio(Sounds::Munch))
            audioManager->playSound(Sounds::Munch, false, VOLUME_MUNCH);
    }
    // Power Pellet Tile -> Blank Tile
    else if(maze->cells[pacMan->getCellX()][pacMan->getCellY()] == 27) {
        maze->cells[pacMan->getCellX()][pacMan->getCellY()] = 30;
        redGhost->setGhostFrightened(true);
        pinkGhost->setGhostFrightened(true);
        blueGhost->setGhostFrightened(true);
        orangeGhost->setGhostFrightened(true);

        if(audioManager->isPlayingAudio(Sounds::Siren))
            audioManager->stopSound(Sounds::Siren);
        if(audioManager->isPlayingAudio(Sounds::Munch))
            audioManager->stopSound(Sounds::Munch);
        audioManager->playSound(Sounds::PowerSnack, false, VOLUME);
    }
}

/**
 * replace siren audio with another sound
 * @param sound - to be played
 * @param isLoop - whether to play on a loop or no
 * @param volume - volume to be played in
 */
void GamePlay::stopSirenAndLoop(Sounds sound, bool isLoop, int volume) {
    if(audioManager->isPlayingAudio(Sounds::Siren))
        audioManager->stopSound(Sounds::Siren);
    if(audioManager->isPlayingAudio(Sounds::Munch))
        audioManager->stopSound(Sounds::Munch);
    audioManager->playSound(sound, isLoop, volume);
    while(audioManager->isPlayingAudio(sound))
        continue;
    audioManager->playSound(Sounds::Siren, true, VOLUME_SIREN);
}