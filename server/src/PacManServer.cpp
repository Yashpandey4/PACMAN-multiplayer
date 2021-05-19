//
// Created by prats on 28/4/21.
//

#include <server/PacManServer.h>
#include <server/MazeServer.h>
#include <iostream>
/**
 * Keeps track of the directions turns for a PacMan object
 * @param direction - takes one of five possible values
 */
void PacManServer::queueDirection(Direction direction) {
    //std::cout << "hello..adding" << std::endl;
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

/*void PacMan::setDirection(Direction direction1) {
    direction = direction1;
}*/

/**
 * Constructor to initialise the PacMan game object
 */
PacManServer::PacManServer(int initialX, int initialY) : CharacterServer(initialX, initialY) {
    eatenPelletsCount = 0;
}

/**
 * Defines movement rules for the PacMan character object in the game
 */
void PacManServer::movePacman() {
    //std::cout << "Bye prends" << std::endl;
    if(!directions.empty()) {
        //std::cout << "hello prends" << std::endl;
        switch (directions.front()) {
            case Direction::UP:{
                //std::cout << "UP" << std::endl;
                CharacterServer::move(0, -PACMAN_SPEED);
                break;
            }
            case Direction::DOWN:{
                //std::cout << "DOWN" << std::endl;
                CharacterServer::move(0, PACMAN_SPEED);
                break;
            }
            case Direction::LEFT:{
               // std::cout << "LEFT" << std::endl;
                CharacterServer::move(-PACMAN_SPEED, 0);
                break;
            }
            case Direction::RIGHT:{
                //std::cout << "RIGHT" << std::endl;
                CharacterServer::move(PACMAN_SPEED, 0);
                break;
            }
            //std::cout << "NONE" << std::endl;
        }
    }
}

/**
 * Getter for directions queue
 * @return directions queue
 */
const std::queue<Direction> &PacManServer::getDirections() const {
    return directions;
}

/**
 * Stops pacman from going through walls or exiting the game screen
 */
void PacManServer::stopPacman() {
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

/**
 * Increase eaten pellets count by the player
 */
void PacManServer::eatPellets() {
    eatenPelletsCount++;
}

/**
 * Returns the number of pellets eaten by PacMan
 * @return number of pellets eaten by PacMan
 */
int PacManServer::getPelletsEaten() const {
    return eatenPelletsCount;
}

/**
 * Getter for pacmanDead
 * @return True if Pacman is dead
 */
bool PacManServer::isPacmanDead() const {
    return pacmanDead;
}

/**
 * Setter for pacmanDead
 * @param pacmanDead
 */
void PacManServer::setPacmanDead(bool pacmanDead) {
    PacManServer::pacmanDead = pacmanDead;
}



