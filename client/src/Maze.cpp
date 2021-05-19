#include "client/Maze.h"
#include "client/GamePlay.h"
#include<unistd.h>
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>

/**
 * Each tile means something different.
 * 0: Snack.
 * 1: Wall.
 * 2: Ghost House.
 * 3: Power snack.
 * 4: Empty.
 */
void generate();
void enlarge();
const int height = 10;
int grid[height][5];
int temp[height*3][15];
int final_path[height*3][30];
int final_tiles[height*3][30];
int temp_cells[height*3 + 4][30];
int temp2[30][height*3 + 4];
int x = 10;

/**
 * Constructor or initialiser for Maze
 * Give codes to the randomly generated maze
 */
Maze::Maze(){
    srand((unsigned)time(0));
    generate();
    enlarge();
    for(int i = 0; i < height*3; i++){
        for(int j = 0; j < 30; j++){
            temp_cells[i + 2][j] = final_tiles[i][j];
        }
    }
    for(int j = 0; j < 30; j++){
        temp_cells[0][j] = 4;
        temp_cells[1][j] = 4;
        temp_cells[height*3 + 2][j] = 4;
        temp_cells[height*3 + 3][j] = 4;
    }
    for(int i = 0; i < height*3 + 4; i++){
        for(int j = 0; j < 30; j++){
            cells[j][i] = temp_cells[i][j];
            temp2[j][i] = temp_cells[i][j];
        }
    }
    for(int i = 10; i < 20; i++){
        cells[i][16] = 1;
        cells[i][19] = 1;
        temp2[i][16] = 1;
        temp2[i][19] = 1;
    }
    for(int j = 16; j < 20; j++){
        cells[10][j] = 1;
        cells[19][j] = 1;
        temp2[10][j] = 1;
        temp2[19][j] = 1;
    }
    for(int j = 2; j < height*3 + 2; j++){
        for(int i = 0; i < 30; i++){
            if(i == 0 || i == 29 || j == 2 || j == height*3 + 1){
                cells[i][j] = 1;
                temp2[i][j] = 1;
            }
            else if(j == 3 || j == height*3 || i == 1 || i == 28){
                cells[i][j] = 0;
                temp2[i][j] = 0;
            }
            else if(cells[i][j] == 2 || cells[i][j] == 4){
                cells[i][j] = 0;
            }
            else if(cells[i][j] == 0){
                
            }
            else if(cells[i][j] != 0){
                cells[i][j] = 1;
                temp2[i][j] = 1;
            }
        }
    }
    cells[16][16] = 2;
    cells[14][16] = 2;
    cells[15][16] = 2;
    cells[29][17] = 4;
    cells[0][17] = 4;
    temp2[16][16] = 2;
    temp2[14][16] = 2;
    temp2[15][16] = 2;
    temp2[29][17] = 4;
    temp2[0][17] = 4;
    for(int i = 11; i < 19; i++){
        for(int j = 17; j < 19; j++){
            cells[i][j] = 4;
            temp2[i][j] = 4;
        }
    }
    int power = 0;
    while(power < 5){
        int i = rand()%29;
        int j = rand()%33;
        if(cells[i][j] == 0){
            cells[i][j] = 3;
            temp2[i][j] = 3;
            power++;
        }
    }
}

/**
 * returns the cell type (orientation of walls) at a particular (x,y) co-ordinate
 * @param x - coordinate
 * @param y - coordinate
 * @return a number from 1-32 corresponding to wall orientation
 */
int Maze::getCellCode(int x, int y) {
    return cells[x][y];
}

/**
 * Determines if character movement is blocked by cell of a specific type - this is done since Pacman and the Ghosts
 * Should be able to move around in the maze but shouldn't be able to go through the walls
 * @param x coordinate
 * @param y coordinate
 * @return True if character is blocked
 */
bool Maze::isCellBlockingCharacter(int x, int y) {
    return (cells[x][y] == 1 || cells[x][y] == 2);
}

/**
 * Identifies intersection tiles in maze
 * @param x coordinate
 * @param y coordinate
 * @return True if intersection
 */
bool Maze::isMazeIntersection(int i, int j)
{
    if((temp2[i][j + 1] == 0 || temp2[i][j + 1] == 3 || temp2[i][j + 1] == 4 || temp2[i][j - 1] == 0 || temp2[i][j - 1] == 3 || temp2[i][j - 1] == 4)
        && (temp2[i + 1][j] == 0 || temp2[i + 1][j] == 3 || temp2[i + 1][j] == 4 || temp2[i - 1][j] == 0 || temp2[i - 1][j] == 3 || temp2[i - 1][j] == 4)
        && (temp2[i][j] == 0 || temp2[i][j] == 3 || temp2[i][j] == 4)){
        return true;
    }
    else{
        return false;
    }
}

/**
 * Generates 5 x 9 grid of random tetris
 */
void generate(){
    int i = 0;
    int j = 0;
    while(j < 5){
        while(i < height){
            x++;
            if(grid[i][j] != 0){
                i++;
                continue;
            }
            int random = (rand()%19) + 1;

            if(random == 1){
                if(i == height - 1 || j == 4){
                    continue;
                }
                if(grid[i + 1][j] != 0 || grid[i][j + 1] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i + 1][j] = x;
                    grid[i][j + 1] = x;
                }
            }

            else if(random == 2){
                if(i == 0 || j == 4){
                    continue;
                }
                if(grid[i - 1][j + 1] != 0 || grid[i][j + 1] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i - 1][j + 1] = x;
                    grid[i][j + 1] = x;
                }
            }

            else if(random == 3){
                if(i == height - 1 || j == 4){
                    continue;
                }
                if(grid[i + 1][j + 1] != 0 || grid[i][j + 1] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i + 1][j + 1] = x;
                    grid[i][j + 1] = x;
                }
            }

            else if(random == 4){
                if(i == height - 1 || j == 4){
                    continue;
                }
                if(grid[i + 1][j] != 0 || grid[i + 1][j + 1] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i + 1][j] = x;
                    grid[i + 1][j + 1] = x;
                }
            }

            else if(random == 5){
                if(i == height - 1 || j >= 3){
                    continue;
                }
                if(grid[i][j + 1] != 0 || grid[i][j + 2] != 0 || grid[i + 1][j] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i][j + 1] = x;
                    grid[i][j + 2] = x;
                    grid[i + 1][j] = x;
                }
            }

            else if(random == 6){
                if(i == 0 || j >= 3){
                    continue;
                }
                if(grid[i][j + 1] != 0 || grid[i][j + 2] != 0 || grid[i - 1][j + 2] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i][j + 1] = x;
                    grid[i][j + 2] = x;
                    grid[i - 1][j + 2] = x;
                }
            }

            else if(random == 7){
                if(i == height - 1 || j >= 3){
                    continue;
                }
                if(grid[i][j + 1] != 0 || grid[i][j + 2] != 0 || grid[i + 1][j + 2] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i][j + 1] = x;
                    grid[i][j + 2] = x;
                    grid[i + 1][j + 2] = x;
                }
            }

            else if(random == 8){
                if(i == height - 1 || j >= 3){
                    continue;
                }
                if(grid[i + 1][j + 1] != 0 || grid[i + 1][j + 2] != 0 || grid[i + 1][j] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i + 1][j + 1] = x;
                    grid[i + 1][j + 2] = x;
                    grid[i + 1][j] = x;
                }
            }

            else if(random == 9){
                if(i == height - 1 || j == 3 || j == 4){
                    continue;
                }
                if(grid[i][j + 1] != 0 || grid[i][j + 2] != 0 || grid[i + 1][j + 1] != 0){
                    continue;
                }
                grid[i][j] = x;
                grid[i][j + 1] = x;
                grid[i][j + 2] = x;
                grid[i + 1][j + 1] = x;
            }

            else if(random == 10){
                if(i == 0 || j == 3 || j == 4){
                    continue;
                }
                if(grid[i][j + 1] != 0 || grid[i][j + 2] != 0 || grid[i - 1][j + 1] != 0){
                    continue;
                }
                grid[i][j] = x;
                grid[i][j + 1] = x;
                grid[i][j + 2] = x;
                grid[i - 1][j + 1] = x;
            }

            else if(random == 11){
                if( i == 0 || i == height - 1 || j == 4){
                    continue;
                }
                if(grid[i + 1][j + 1] != 0 || grid[i - 1][j + 1] != 0 || grid[i][j + 1] != 0){
                    continue;
                }
                grid[i][j] = x;
                grid[i + 1][j + 1] = x;
                grid[i - 1][j + 1] = x;
                grid[i][j + 1] = x;
            }

            else if(random == 12){
                if( i == height - 2 || i == height - 1 || j == 4){
                    continue;
                }
                if(grid[i + 1][j] != 0 || grid[i + 2][j] != 0 || grid[i + 1][j + 1] != 0){
                    continue;
                }
                grid[i][j] = x;
                grid[i + 1][j] = x;
                grid[i + 2][j] = x;
                grid[i + 1][j + 1] = x;
            }

            else if(random == 13){
                if(i >= height - 2 || j == 4){
                    continue;
                }
                if(grid[i + 1][j] != 0 || grid[i + 2][j] != 0 || grid[i][j + 1] != 0){
                    continue;
                }
                grid[i][j] = x;
                grid[i + 1][j] = x;
                grid[i + 2][j] = x;
                grid[i][j + 1] = x;
            }

            else if(random == 14){
                if(i >= height - 2 || j == 4){
                    continue;
                }
                if(grid[i + 1][j + 1] != 0 || grid[i + 2][j + 1] != 0 || grid[i][j + 1] != 0){
                    continue;
                }
                grid[i][j] = x;
                grid[i + 1][j + 1] = x;
                grid[i + 2][j + 1] = x;
                grid[i][j + 1] = x;
            }

            else if(random == 15){
                if(i >= height - 2 || j == 4){
                    continue;
                }
                if(grid[i + 1][j] != 0 || grid[i + 2][j] != 0 || grid[i + 2][j + 1] != 0){
                    continue;
                }
                grid[i][j] = x;
                grid[i + 1][j] = x;
                grid[i + 2][j] = x;
                grid[i + 2][j + 1] = x;
            }

            else if(random == 16){
                if(i <= 1 || j == 4){
                    continue;
                }
                if(grid[i - 1][j + 1] != 0 || grid[i - 2][j + 1] != 0 || grid[i][j + 1] != 0){
                    continue;
                }
                grid[i][j] = x;
                grid[i - 1][j + 1] = x;
                grid[i - 2][j + 1] = x;
                grid[i][j + 1] = x;
            }

            else if(random == 17){
                if(rand()%2 == 0){
                    continue;
                }
                if(j == 4){
                    continue;
                }
                else if(grid[i][j + 1] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i][j + 1] = x;
                }
            }

            else if(random == 18){
                if(rand()%2 == 0){
                    continue;
                }
                if(i == height - 1){
                    continue;
                }
                else if(grid[i + 1][j] != 0){
                    continue;
                }
                else{
                    grid[i][j] = x;
                    grid[i + 1][j] = x;
                }
            }
            else if(random == 19){
                if(rand()%2 == 0){
                    continue;
                }
                    grid[i][j] = -1;
            }
            i++;
        }
        i = 0;
        j++;
    }
}

/**
 * Converts 5 x 9 grid to 15 x 27 grid and then takes reflection, size of final grid is 30 x 27
 */
void enlarge(){
    grid[height/2 - 1][0] = 2;
    grid[height/2 - 1][1] = 2;
    grid[height/2][0] = 2;
    grid[height/2][1] = 2;
    int y = -2;
    for(int i = 0; i < height*3; i++){
        for(int j = 0; j < 15; j++){
            temp[i][j] = grid[i/3][j/3];
        }
    }
    for(int i = 0; i < height*3; i++){
        for(int j = 15; j < 30; j++){
            final_path[i][j] = temp[i][j - 15];
        }
    }
    for(int i = 0; i < height*3; i++){
        for(int j = 0; j < 15; j++){
            final_path[i][j] = temp[i][14 - j]*2;
        }
    }
    for(int i = 0; i < height*3; i++){
        for(int j = 0; j < 30; j++){
            int flag = 0;
            if(i == 0){
                final_tiles[i][j] = 0;
                continue;
            }
            if(i == height*3){
                final_tiles[i][j] = 0;
                continue;
            }
            if(j == 29){
                final_tiles[i][j] = 0;
                continue;
            }
            if(j == 0){
                final_tiles[i][j] = 0;
                continue;
            }
            if(final_path[i][j] == final_path[i][j - 1] && final_path[i][j] == final_path[i][j + 1] 
                && final_path[i][j] == final_path[i + 1][j] && final_path[i][j] == final_path[i - 1][j]
                && final_path[i][j] == final_path[i + 1][j + 1] && final_path[i][j] == final_path[i + 1][j - 1]
                && final_path[i][j] == final_path[i - 1][j + 1] && final_path[i][j] == final_path[i - 1][j - 1]){
                final_tiles[i][j] = final_path[i][j];
            }
            else{
                final_tiles[i][j] = 0;
            }
        }
    }
}