/**
 * Ghost is a subclass of entity to avoid rewriting methods that are common for PACMAN and Ghost
 */

#include "Ghost.h"

/**
 * Constructor or initialiser for Ghosts
 * @param cellPositionX - Initial Ghost Position
 * @param cellPositionY - Initial Ghost Position
 * @param destinationX - Desired Ghost Position
 * @param destinationY - Desired Ghost Position
 */
Ghost::Ghost(int cellPositionX, int cellPositionY, int destinationX, int destinationY)
    : Character(cellPositionX, cellPositionY){
    setGhostDestination(destinationX, destinationY);
    setDirection(Direction::UNSET);
    scatterGhosts = true;
    ghostOutOfCage = false;
    ghostDecision = true;
    ghostFrightened = false;
}

/**
 * Sets target destination of ghosts to be (x,y) target coordinates
 * @param x - coordinate
 * @param y - coordinate
 */
void Ghost::setGhostDestination(int x, int y) {
    destinationX = x;
    destinationY = y;
}

/**
 * Handles Ghost Movements
 */
void Ghost::moveGhost() {
    switch(direction) {
        case Direction::UP:
            Character::move(0,-GHOST_SPEED);
            break;
        case Direction::DOWN:
            Character::move(0,GHOST_SPEED);
            break;
        case Direction::LEFT:
            Character::move(-GHOST_SPEED,0);
            break;
        case Direction::RIGHT:
            Character::move(GHOST_SPEED,0);
            break;
    }
}

/**
 * Getter for Destination X coordinate
 * @return DestinationX
 */
int Ghost::getDestinationX() const {
    return destinationX;
}

/**
 * Getter for Destination Y coordinate
 * @return DestinationY
 */
int Ghost::getDestinationY() const {
    return destinationY;
}

/**
 * Getter for Direction
 * @return Direction
 */
Direction Ghost::getDirection() const {
    return direction;
}

/**
 * Setter for Direction
 * @param direction
 */
void Ghost::setDirection(Direction direction) {
    Ghost::direction = direction;
}

/**
 * Setter for scatterGhosts
 * @param scatterGhosts
 */
void Ghost::setScatterGhosts(bool scatterGhosts) {
    Ghost::scatterGhosts = scatterGhosts;
}

/**
 * Setter for ghostDecision
 * @param ghostDecision
 */
void Ghost::setGhostDecision(bool ghostDecision) {
    Ghost::ghostDecision = ghostDecision;
}

/**
 * Setter for ghostFrightened
 * @param ghostFrightened
 */
void Ghost::setGhostFrightened(bool ghostFrightened) {
    if(ghostFrightened)
        Ghost::ghostFrightened = 2000;
    else
        Ghost::ghostFrightened = 0;
}

/**
 * Getter for scatterGhosts
 * @return scatterGhosts
 */
bool Ghost::isScatterGhosts() const {
    return scatterGhosts;
}

/**
 * Getter for ghostOutOfCage
 * @return ghostOutOfCage
 */
bool Ghost::isGhostOutOfCage() const {
    return ghostOutOfCage;
}

/**
 * Getter for ghostDecision
 * @return ghostDecision
 */
bool Ghost::isGhostDecision() const {
    return ghostDecision;
}

/**
 * Getter for ghostFrightened
 * @return ghostFrightened
 */
int Ghost::getGhostFrightened() {
    if (ghostFrightened > 0 )
        ghostFrightened--;
    return ghostFrightened > 0;
}

/**
 * Transports the ghost to the given (x,y) target coordinates
 * @param x - coordinate
 * @param y - coordinate
 */
void Ghost::ghostTeleport(int x, int y) {
    Character::teleport(x, y);
    ghostOutOfCage = true;
}

