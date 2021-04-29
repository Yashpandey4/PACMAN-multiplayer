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

public:
    PacMan();
    constexpr static const float PACMAN_SPEED = 0.04f;
    const std::queue<Direction> &getDirections() const;
    void queueDirection(Direction direction);
    void movePacman();
    void stopPacman();
};


#endif //PACMAN_2PLAYER_PACMAN_H
