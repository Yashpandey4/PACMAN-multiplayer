/**
 * This file is a superclass for the PacMan and Ghost character files, encapsulating the common functions and member variables
 */

#include <server/CharacterServer.h>
#include <cmath>
#include <SFML/Network.hpp>
#include <iostream>

/**
 * Constructor for a character object
 * @param cellPositionX - initial x position of character on display
 * @param cellPositionY - initial y position of character on display
 */
CharacterServer::CharacterServer(int cellPositionX, int cellPositionY) {
    cellX = cellPositionX;
    cellY = cellPositionY;
    screenPositionX = (cellPositionX + 1.0f) * 16.0f;
    screenPositionY = (2.0f * cellPositionY + 1.0f) * 8.0f;
}

/**
 * Getter for ScreenPositionX
 * @return ScreenPositionX
 */
float CharacterServer::getScreenPositionX() const {
    return screenPositionX;
}

/**
 * Getter for ScreenPositionY
 * @return ScreenPositionY
 */
float CharacterServer::getScreenPositionY() const {
    return screenPositionY;
}

/**
 * Getter for getCellX
 * @return getCellX
 */
int CharacterServer::getCellX() const {
    return cellX;
}

/**
 * Getter for getCellY
 * @return getCellY
 */
int CharacterServer::getCellY() const {
    return cellY;
}

/**
 * Handles character movement on-screen
 * @param x - x coordinates to move the character by
 * @param y - y coordinates to move the character by
 */
void CharacterServer::move(float x, float y) {
    screenPositionX += x;
    screenPositionY += y;
    //std::cout << "3: " << screenPositionX << " - " << screenPositionY << std::endl;

    if ((int)(screenPositionX + 8) % 16 == 0 && (int)(screenPositionY + 8) % 16 == 0)
    {
        cellX = (int) round((screenPositionX - 8) / 16);
        cellY = (int) round((screenPositionY - 8) / 16);
        //std::cout << "3: " << cellX << " - " << cellY << std::endl;
    }
}

/**
 * Transports the character to the given (x,y) target coordinates
 * @param x - coordinate
 * @param y - coordinate
 */
void CharacterServer::teleport(int x, int y) {
    cellX = x;
    cellY = y;
    screenPositionX = x * 16.0f + 8.0f;
    screenPositionY = y * 16.0f + 8.0f;
}

/*sf::Packet& operator <<(sf::Packet& packet, const Character& character){
    return packet << character.cellX << character.cellY;
}

sf::Packet& operator >>(sf::Packet& packet, Character& character)
{
    return packet >> character.cellX >> character.cellY;
}*/

