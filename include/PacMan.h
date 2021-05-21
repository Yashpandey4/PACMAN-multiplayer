//
// Created by prats on 28/4/21.
//

#ifndef PACMAN_2PLAYER_PACMAN_H
#define PACMAN_2PLAYER_PACMAN_H

#include <queue>
#include "Direction.h"
#include "Character.h"

class PacMan : public Character {
private:
    Direction direction;
    int eatenPelletsCount;
    bool pacmanDead;
    int destinationX;
    int destinationY;
    bool pacmanDecision;

public:

    const std::vector<std::pair<int,int>> moves_true = {
            {1, 26},
            {26, 26},
            {26,  6},
            {1, 6},
            {13, 26}
    };

    const std::vector<std::pair<int,int>> moves = {
            {2, 25},
            {27, 25},
            {27,  5},
            {1, 5},
            {13, 26}
    };


    PacMan(int destinationX, int destinationY);

    constexpr static const float PACMAN_SPEED = 0.04f;

    void movePacman();

    void eatPellets();

    int getPelletsEaten() const;

    bool isPacmanDead() const;

    void setPacmanDead(bool pacmanDead);

    void setPacManDestination(int x, int y);

    int getDestinationX() const;

    int getDestinationY() const;

    Direction getDirection() const;

    void setDirection(Direction direction);

    bool isPacmanDecision() const;

    void setPacmanDecision(bool pacmanDecision);
};


#endif //PACMAN_2PLAYER_PACMAN_H
