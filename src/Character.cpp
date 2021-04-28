/**
 * This file is a superclass for the PacMan and Ghost character files, encapsulating the common functions and member variables
 */

#include "Character.h"

Character::Character(int cellPositionX, int cellPositionY) {
    cellX = cellPositionX;
    cellY = cellPositionY;
    screenPositionX = (cellPositionX + 1.0f) * 16.0f;
    screenPositionY = (2.0f * cellPositionY + 1.0f) * 8.0f;
}

float Character::getScreenPositionX() const {
    return screenPositionX;
}

float Character::getScreenPositionY() const {
    return screenPositionY;
}

int Character::getCellX() const {
    return cellX;
}

int Character::getCellY() const {
    return cellY;
}
