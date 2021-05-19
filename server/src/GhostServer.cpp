/**
 * Ghost is a subclass of entity to avoid rewriting methods that are common for PACMAN and Ghost
 */

#include <server/GhostServer.h>

/**
 * Constructor or initialiser for Ghosts
 * @param cellPositionX - Initial Ghost Position
 * @param cellPositionY - Initial Ghost Position
 * @param destinationX - Desired Ghost Position
 * @param destinationY - Desired Ghost Position
 */
GhostServer::GhostServer(int cellPositionX, int cellPositionY, int destinationX, int destinationY)
    : CharacterServer(cellPositionX, cellPositionY){
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
void GhostServer::setGhostDestination(int x, int y) {
    destinationX = x;
    destinationY = y;
}

/**
 * Handles Ghost Movements
 */
void GhostServer::moveGhost() {
    switch(direction) {
        case Direction::UP:
            CharacterServer::move(0,-GHOST_SPEED);
            break;
        case Direction::DOWN:
            CharacterServer::move(0,GHOST_SPEED);
            break;
        case Direction::LEFT:
            CharacterServer::move(-GHOST_SPEED,0);
            break;
        case Direction::RIGHT:
            CharacterServer::move(GHOST_SPEED,0);
            break;
    }
}

/**
 * Getter for Destination X coordinate
 * @return DestinationX
 */
int GhostServer::getDestinationX() const {
    return destinationX;
}

/**
 * Getter for Destination Y coordinate
 * @return DestinationY
 */
int GhostServer::getDestinationY() const {
    return destinationY;
}

/**
 * Getter for Direction
 * @return Direction
 */
Direction GhostServer::getDirection() const {
    return direction;
}

/**
 * Setter for Direction
 * @param direction
 */
void GhostServer::setDirection(Direction direction) {
    GhostServer::direction = direction;
}

/**
 * Setter for scatterGhosts
 * @param scatterGhosts
 */
void GhostServer::setScatterGhosts(bool scatterGhosts) {
    GhostServer::scatterGhosts = scatterGhosts;
}

/**
 * Setter for ghostDecision
 * @param ghostDecision
 */
void GhostServer::setGhostDecision(bool ghostDecision) {
    GhostServer::ghostDecision = ghostDecision;
}

/**
 * Setter for ghostFrightened
 * @param ghostFrightened
 */
void GhostServer::setGhostFrightened(bool ghostFrightened) {
    if(ghostFrightened)
        GhostServer::ghostFrightened = 8000;
    else
        GhostServer::ghostFrightened = 0;
}

/**
 * Getter for scatterGhosts
 * @return scatterGhosts
 */
bool GhostServer::isScatterGhosts() const {
    return scatterGhosts;
}

/**
 * Getter for ghostOutOfCage
 * @return ghostOutOfCage
 */
bool GhostServer::isGhostOutOfCage() const {
    return ghostOutOfCage;
}

/**
 * Getter for ghostDecision
 * @return ghostDecision
 */
bool GhostServer::isGhostDecision() const {
    return ghostDecision;
}

/**
 * Getter for ghostFrightened
 * @return ghostFrightened
 */
int GhostServer::isGhostFrightened() {
    if (ghostFrightened > 0 )
        ghostFrightened--;
    return ghostFrightened > 0;
}

/**
 * Transports the ghost to the given (x,y) target coordinates
 * @param x - coordinate
 * @param y - coordinate
 */
void GhostServer::teleport(int x, int y) {
    CharacterServer::teleport(x, y);
    ghostOutOfCage = true;
}

