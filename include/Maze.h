//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_MAZE_H
#define PACMAN_2PLAYER_MAZE_H


class Maze
{
public:
    static const int SIZE_X = 28;
    static const int SIZE_Y = 36;

    Maze();
    int getCellCode(int x, int y);

private:
    int cells[SIZE_X][SIZE_Y];
};


#endif //PACMAN_2PLAYER_MAZE_H
