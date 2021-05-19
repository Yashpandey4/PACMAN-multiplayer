//
// Created by prats on 28/4/21.
//

#include "PacMan.h"

/**
 * Keeps track of the directions turns for a PacMan object
 * @param direction - takes one of five possible values
 */
void PacMan::queueDirection(Direction direction) {

    // If the direction inputted is opposite to the other directions, clear the direction queue
    if(!directions.empty()) {
        if(direction == -directions.front()) {
            std::queue<Direction> empty;
            std::swap(directions, empty);
        }
    }

    // Wait for initial inputs to be acted on before you input new ones (avoids overfilling of the queue)
    if(directions.size() < 2)
        directions.push(direction);
}

/**
 * Constructor to initialise the PacMan game object
 */
PacMan::PacMan() : Character(13, 26) {

}

/**
 * Defines movement rules for the PacMan character object in the game
 */
void PacMan::move() {
    if(!directions.empty()) {
        switch (directions.front()) {
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
}

/**
 * Getter for directions queue
 * @return directions queue
 */
const std::queue<Direction> &PacMan::getDirections() const {
    return directions;
}

/**
 * Stops pacman from going through walls or exiting the game screen
 */
void PacMan::stopMoving() {
    if(directions.size() > 1) {
        if((int)(screenPositionX + 8) % 16 == 0 && (int)(screenPositionY + 8) % 16 == 0) {
            switch (directions.front())
            {
                case Direction::UP:
                    directions.pop();
                    break;
                case Direction::DOWN:
                    directions.pop();
                    break;
                case Direction::LEFT:
                    directions.pop();
                    break;
                case Direction::RIGHT:
                    directions.pop();
                    break;
            }
        }
    }
}



