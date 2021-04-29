//
// Created by prats on 29/4/21.
//

#ifndef PACMAN_2PLAYER_GHOST_H
#define PACMAN_2PLAYER_GHOST_H


#include "Character.h"
#include "Direction.h"

class Ghost : public Character {
private:
    int destinationX;

    int destinationY;

    Direction direction;

public:
    void setDirection(Direction direction);

    Ghost(int cellPositionX, int cellPositionY, int destinationX, int destinationY);

    constexpr static const float GHOST_SPEED = 0.03f;

    void setGhostDestination(int x, int y);

    void moveGhost();

    int getDestinationX() const;

    int getDestinationY() const;

    Direction getDirection() const;

};


#endif //PACMAN_2PLAYER_GHOST_H
