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
    std::queue<Direction> directions;
    int eatenPelletsCount;
    bool pacmanDead;

public:
    PacMan(int initialX, int initialY);

    constexpr static const float PACMAN_SPEED = 0.04f;

    const std::queue<Direction> &getDirections() const;

    void queueDirection(Direction direction);

    void movePacman();

    void stopPacman();

    void eatPellets();

    int getPelletsEaten() const;

    bool isPacmanDead() const;

    void setPacmanDead(bool pacmanDead);
};


#endif //PACMAN_2PLAYER_PACMAN_H
