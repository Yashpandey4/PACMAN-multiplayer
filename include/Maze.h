//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_MAZE_H
#define PACMAN_2PLAYER_MAZE_H

#include "PacMan.h"
#include "Ghost.h"

class Maze
{
public:
    static const int SIZE_X = 28;
    static const int SIZE_Y = 36;

    Maze();

    int getCellCode(int x, int y);

    bool isCellBlockingCharacter(int x, int y);

    static bool isMazeIntersection(int x, int y);

    void removePellets(PacMan* pacMan, Ghost* ghost1, Ghost* ghost2, Ghost* ghost3, Ghost* ghost4);

private:
    int cells[SIZE_X][SIZE_Y];
};


#endif //PACMAN_2PLAYER_MAZE_H
