//
// Created by prats on 27/4/21.
//

#ifndef PACMAN_2PLAYER_MAZE_H
#define PACMAN_2PLAYER_MAZE_H


class Maze
{
public:
    static const int SizeX = 28;
    static const int SizeY = 36;

    Maze();
    int getTileCode(int x, int y);

private:
    int tiles[SizeX][SizeY];
};


#endif //PACMAN_2PLAYER_MAZE_H
