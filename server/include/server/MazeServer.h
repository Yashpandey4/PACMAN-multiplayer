//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_MAZE_H
#define PACMAN_2PLAYER_MAZE_H

#include "PacManServer.h"
#include "GhostServer.h"

class MazeServer
{
public:
    static const int SIZE_X = 30;
    static const int SIZE_Y = 34;

    MazeServer();

    int getCellCode(int x, int y);

    bool isCellBlockingCharacter(int x, int y);

    static bool isMazeIntersection(int x, int y);

    int cells[SIZE_X][SIZE_Y];
};


#endif //PACMAN_2PLAYER_MAZE_H
