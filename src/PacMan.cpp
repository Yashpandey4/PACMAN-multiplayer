//
// Created by prats on 28/4/21.
//

#include "PacMan.h"


/**
 * Constructor to initialise the PacMan game object
 */
PacMan::PacMan(int destinationX, int destinationY) : Character(12, 26) {
    eatenPelletsCount = 0;
    pacmanDecision = true;
    setPacManDestination(destinationX, destinationY);
    setDirection(Direction::UNSET);
}

/**
 * Sets target destination of ghosts to be (x,y) target coordinates
 * @param x - coordinate
 * @param y - coordinate
 */
void PacMan::setPacManDestination(int x, int y) {
    destinationX = x;
    destinationY = y;
}

/**
 * Defines movement rules for the PacMan character object in the game
 */
void PacMan::movePacman() {
    switch (direction) {
        case Direction::UP:
            Character::move(0, -PACMAN_SPEED);
            break;
        case Direction::DOWN:
            Character::move(0, PACMAN_SPEED);
            break;
        case Direction::LEFT:
            Character::move(-PACMAN_SPEED, 0);
            break;
        case Direction::RIGHT:
            Character::move(PACMAN_SPEED, 0);
            break;
    }
}

/**
 * Increase eaten pellets count by the player
 */
void PacMan::eatPellets() {
    eatenPelletsCount++;
}

/**
 * Returns the number of pellets eaten by PacMan
 * @return number of pellets eaten by PacMan
 */
int PacMan::getPelletsEaten() const {
    return eatenPelletsCount;
}

/**
 * Getter for pacmanDead
 * @return True if Pacman is dead
 */
bool PacMan::isPacmanDead() const {
    return pacmanDead;
}

/**
 * Setter for pacmanDead
 * @param pacmanDead
 */
void PacMan::setPacmanDead(bool pacmanDead) {
    PacMan::pacmanDead = pacmanDead;
}

int PacMan::getDestinationX() const {
    return destinationX;
}

int PacMan::getDestinationY() const {
    return destinationY;
}

Direction PacMan::getDirection() const {
    return direction;
}

void PacMan::setDirection(Direction direction) {
    PacMan::direction = direction;
}

bool PacMan::isPacmanDecision() const {
    return pacmanDecision;
}

void PacMan::setPacmanDecision(bool pacmanDecision) {
    PacMan::pacmanDecision = pacmanDecision;
}



