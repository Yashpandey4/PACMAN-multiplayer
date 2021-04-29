/**
 * Ghost is a subclass of entity to avoid rewriting methods that are common for PACMAN and Ghost
 */

#include "Ghost.h"

/**
 *
 * @param cellPositionX
 * @param cellPositionY
 * @param destinationX
 * @param destinationY
 */
Ghost::Ghost(int cellPositionX, int cellPositionY, int destinationX, int destinationY)
    : Character(cellPositionX, cellPositionY){
    setGhostDestination(destinationX, destinationY);
}

/**
 *
 * @param x
 * @param y
 */
void Ghost::setGhostDestination(int x, int y) {
    destinationX = x;
    destinationY = y;
}

/**
 *
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
 *
 * @return
 */
int Ghost::getDestinationX() const {
    return destinationX;
}

/**
 *
 * @return
 */
int Ghost::getDestinationY() const {
    return destinationY;
}

/**
 *
 * @return
 */
Direction Ghost::getDirection() const {
    return direction;
}

/**
 *
 * @param direction
 */
void Ghost::setDirection(Direction direction) {
    Ghost::direction = direction;
}
