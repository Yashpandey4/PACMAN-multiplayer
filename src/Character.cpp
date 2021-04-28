/**
 * This file is a superclass for the PacMan and Ghost character files, encapsulating the common functions and member variables
 */

#include "Character.h"

/**
 * Constructor for a character object
 * @param cellPositionX - initial x position of character on display
 * @param cellPositionY - initial y position of character on display
 */
Character::Character(int cellPositionX, int cellPositionY) {
    cellX = cellPositionX;
    cellY = cellPositionY;
    screenPositionX = (cellPositionX + 1.0f) * 16.0f;
    screenPositionY = (2.0f * cellPositionY + 1.0f) * 8.0f;
}

/**
 * Getter for ScreenPositionX
 * @return ScreenPositionX
 */
float Character::getScreenPositionX() const {
    return screenPositionX;
}

/**
 * Getter for ScreenPositionY
 * @return ScreenPositionY
 */
float Character::getScreenPositionY() const {
    return screenPositionY;
}

/**
 * Getter for getCellX
 * @return getCellX
 */
int Character::getCellX() const {
    return cellX;
}

/**
 * Getter for getCellY
 * @return getCellY
 */
int Character::getCellY() const {
    return cellY;
}

/**
 * Handles character movement on-screen
 * @param x - x coordinates to move the character by
 * @param y - y coordinates to move the character by
 */
void Character::move(float x, float y) {
    screenPositionX += x;
    screenPositionY += y;
}

